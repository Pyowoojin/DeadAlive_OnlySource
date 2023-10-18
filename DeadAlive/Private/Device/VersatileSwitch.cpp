#include "Device/VersatileSwitch.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Device/BulbActor.h"
#include "Kismet/GameplayStatics.h"
#include "Spawner/EnemySpawner.h"

AVersatileSwitch::AVersatileSwitch()
{
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshComponent);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionBox->SetupAttachment(GetRootComponent());

	// InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
}

void AVersatileSwitch::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AVersatileSwitch::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AVersatileSwitch::OnBoxOverlapEnd);
	
}

void AVersatileSwitch::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor->ActorHasTag("Player")) return ;

	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	// UE_LOG(LogTemp, Warning, TEXT("비긴 오벌랩"));
}

void AVersatileSwitch::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!OtherActor->ActorHasTag("Player")) return ;

	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	// UE_LOG(LogTemp, Warning, TEXT("엔드 오벌랩"));
}

void AVersatileSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVersatileSwitch::InteractWithThisActor()
{
	IInteractInterface::InteractWithThisActor();

	bIsActive = true;
	
	if(!BulbArray.IsEmpty())
	{
		for(auto i : BulbArray)
		{
			i->PointLight->SetVisibility(true);
		}
	}

	if(Spawner)
	{
		Spawner->SpawnEnemy(EnemySpawnCount, SpawnPoint, EnemyTargetPoint->GetActorLocation(), EnemySpawnDelay, EnemySpawnCycle);
	}

	if(Spawner2)
	{
		Spawner2->SpawnEnemy(EnemySpawnCount, SpawnPoint, EnemyTargetPoint->GetActorLocation(), EnemySpawnDelay, EnemySpawnCycle);
	}
}

void AVersatileSwitch::TestFunc()
{
}
