#include "Items/EnemyWeapon.h"

#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemyWeapon::AEnemyWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBoxCollision"));
	BoxCollision->SetWorldScale3D(FVector(0.5f, 0.7f, 1.3f));
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(BoxCollision);
	TraceStart->SetRelativeLocation(FVector(0.f, 0.f, -35.f));
	
	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(BoxCollision);
	TraceEnd->SetRelativeLocation(FVector(0.f, 0.f, 35.f));
	
}
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWeapon::DamageInstigate);
	// BoxCollision->OnComponentHit
	
}
void AEnemyWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::KeepRelative, true);
	this->AttachToComponent(InParent, TransformRules, InSocketName);
	this->SetOwner(NewOwner);
}

void AEnemyWeapon::DamageInstigate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult HitResult;
	ResultOfSlash(HitResult);
	if(HitResult.GetActor())
	{
		// UE_LOG(LogTemp, Warning, TEXT("%d"), bFromSweep);
		
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
		if(APlayerCharacter* BeHitActor = Cast<APlayerCharacter>(HitResult.GetActor()))
		{
			BeHitActor->GetHit(HitResult.ImpactPoint, this->Owner, this->WeaponDamage);
		}
	}

	IgnoreActors.Empty();
	
}

void AEnemyWeapon::DamageApply(IHitInterface* AppliedActor, AActor* Hitter)
{
	AppliedActor->GetHit(FVector(0.f, 0.f, 0.f), Hitter, WeaponDamage);
}

float AEnemyWeapon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return ActualDamage;
}

void AEnemyWeapon::ResultOfSlash(FHitResult& HitResult)
{
	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(this->Owner);

	for(auto Actor : IgnoreActors)
	{
		ActorsToIgnore.Add(Actor);
	}
	
	
	UKismetSystemLibrary::BoxTraceSingle(GetWorld(),
		Start,
		End,
		BoxCollision->GetScaledBoxExtent() / 2,
		BoxCollision->GetComponentRotation(),
		TraceTypeQuery2,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Blue,
		FLinearColor::Green,
		3.f);

	IgnoreActors.AddUnique(HitResult.GetActor());
}

void AEnemyWeapon::SetWeaponNoCollision()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyWeapon::SetWeaponCollision()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
