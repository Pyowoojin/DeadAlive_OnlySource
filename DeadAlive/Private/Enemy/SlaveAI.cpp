#include "Enemy/SlaveAI.h"
#include "Attributes/CharacterAttribute.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/BaseWeapon.h"

ASlaveAI::ASlaveAI()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	CharAttribute = CreateDefaultSubobject<UCharacterAttribute>(TEXT("CharacterAttributes"));
	
}

void ASlaveAI::BeginPlay()
{
	Super::BeginPlay();
	/*const FString RelativePath = TEXT("/Game/Blueprint/Item/Weapon/BP_SlaveAIWeapon");
	
	if(UBlueprint* BlueprintAsset = Cast<UBlueprint>(LoadObject<UBlueprint>(nullptr, *RelativePath)))
	{
		
		if(UClass* BlueprintClass = BlueprintAsset->GeneratedClass)
		{
			ABaseWeapon* EquipWeapon = GetWorld()->SpawnActor<ABaseWeapon>(BlueprintClass);
			CharAttribute->SetEquippedWeapon(EquipWeapon);
			CharAttribute->GetEquippedWeapon()->ItemAcquisition(this->GetMesh(), this);
		}
	}*/
	if(!SlaveWeapon.IsNull())
	{
		if(UClass* BlueprintClass = SlaveWeapon.LoadSynchronous())
		{
			ABaseWeapon* EquipWeapon = GetWorld()->SpawnActor<ABaseWeapon>(BlueprintClass);
			CharAttribute->SetEquippedWeapon(EquipWeapon);
			CharAttribute->GetEquippedWeapon()->ItemAcquisition(this->GetMesh(), this);
		}
	}
	
}

void ASlaveAI::FaceRotation(FRotator NewControlRotation, float DeltaTime)
{
	Super::FaceRotation(NewControlRotation, DeltaTime);
}

void ASlaveAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASlaveAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

