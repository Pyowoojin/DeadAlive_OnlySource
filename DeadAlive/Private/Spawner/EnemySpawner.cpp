#include "Spawner/EnemySpawner.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComponent->SetupAttachment(GetRootComponent());

}
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	InitSpawner();
	if(WaveSound)
	{
		AudioComponent->SetSound(WaveSound);
	}
	
}
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::InitSpawner()
{
	CreateEnemy(2);
}

void AEnemySpawner::OnEnemyDead(AEnemyCharacter* Enemy)
{
	DeathCount--;
	EnemyObjectPool.Push(Enemy);
	CurrentEnemyObjectPoolSize++;

	if(DeathCount == 0)
		WaveStop();
}

void AEnemySpawner::SpawnFromObjectPool(const AActor* SpawnLocation, const FVector& TargetLocation)
{
	if(EnemyObjectPool.IsEmpty()) return ;
	UE_LOG(LogTemp, Warning, TEXT("생성완뇨"));
	EnemyObjectPool.Top()->EnemyActive();
	// 소환 위치 지정
	EnemyObjectPool.Top()->SetActorLocation(SpawnLocation->GetActorLocation());
	EnemyObjectPool.Top()->MoveToPoint(TargetLocation);
	EnemyObjectPool.Pop();
	CurrentEnemyObjectPoolSize--;
}

// 몬스터를 스폰한다. 오브젝트 풀에 남은 몬스터가 없으면 더 생성해서 풀에 넣어줌
void AEnemySpawner::SpawnEnemy(const int32 SpawnCount, const AActor* SpawnLocation, const FVector& TargetLocation, float SpawnDelay, int32 SpawnCycle)
{
	WaveStart();
	const int32 TotalSpawnCount = SpawnCount * SpawnCycle;
	DeathCount = TotalSpawnCount;
	auto SpawnTimerCallback = [this, SpawnLocation, TargetLocation]()
	{
		SpawnFromObjectPool(SpawnLocation, TargetLocation);
	};

	// 현재 5마리 사용 가능, 9마리를 스폰할 것이라면 몬스터 (9 - 5 = )4마리 추가로 생성
	if(CurrentEnemyObjectPoolSize < TotalSpawnCount)
	{
		CreateEnemy(TotalSpawnCount-CurrentEnemyObjectPoolSize);
	}

	/*for(int32 i = 0; i < SpawnCount; i++)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, SpawnTimerCallback, i* SpawnDelay, false);
		// SpawnFromObjectPool(SpawnLocation, TargetLocation);
	}*/
	GetWorldTimerManager().SetTimer(SpawnTimer, SpawnTimerCallback, SpawnDelay, true); // 0.1 초마다 실행
	GetWorldTimerManager().SetTimer(StopSpawnTimer, this, &AEnemySpawner::StopSpawnTimerFunc, SpawnCount * SpawnCycle); // 0.3초 후에 종료

	if(SpawnLocation == nullptr)
	{
		SpawnLocation = this;
	}
	
}

void AEnemySpawner::StopSpawnTimerFunc()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	UE_LOG(LogTemp, Warning, TEXT("실행하였스빈다"));
}

void AEnemySpawner::EnemyWork()
{
	for(auto i : EnemyObjectPool)
	{
		i->SetActorTickEnabled(true);
		i->SetActorEnableCollision(true);
		i->SetActorHiddenInGame(false);
		i->SetActorLocation(SpawnLocationActor->GetActorLocation());
		i->MoveToPoint(DestinationActor);
	}
}

void AEnemySpawner::WaveStart()
{
	IsClear = false;
	if(AudioComponent)
	{
		AudioComponent->Play();
	}
}

void AEnemySpawner::WaveStop()
{
	IsClear = true;
	if(AudioComponent)
	{
		AudioComponent->FadeOut(3, 0.f);
	}
}

// SpawnCount 만큼 Enemy Spawn해주기
void AEnemySpawner::CreateEnemy(const int32 SpawnCount)
{
	for(int32 i = 0; i< SpawnCount; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto PoolableActor = GetWorld()->SpawnActor<AEnemyCharacter>(PooledObjectClass, FVector().Zero(), FRotator().ZeroRotator, SpawnParams);
		if(PoolableActor)
		{
			// UE_LOG(LogTemp,Warning, TEXT("적을 생성하였습니다."))
			// 스포너를 이것으로 지정해줌
			PoolableActor->SetOwnedSpawner(this);

			// 죽음 알림 델리게이트 설정
			PoolableActor->EnemyDelegate.BindUObject(this, &AEnemySpawner::OnEnemyDead);

			// 우선 게임에서 숨겨줌. 소환이 된다면 게임에 나타나게 할 것임
			PoolableActor->SetActorHiddenInGame(true);
			PoolableActor->SetActorEnableCollision(false);
			PoolableActor->SetActorTickEnabled(false);
			EnemyObjectPool.Push(PoolableActor);

			++CurrentEnemyObjectPoolSize;
			MaxEnemyObjectsSize++;
		}
	}
}
