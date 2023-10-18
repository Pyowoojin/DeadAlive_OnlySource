#include "Items/ArmorItems.h"

#include "PlayerCharacter.h"
#include "Attributes/CharacterAttribute.h"
#include "CustomComponent/EquipmentComponent.h"
#include "HUD/Inventory/HUD_InventorySystem.h"

AArmorItems::AArmorItems()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AArmorItems::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArmorItems::SetupArmorCollision()
{
	SkeletalComponent->SetSimulatePhysics(false);
	SkeletalComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCollisionDisable();
	PlayPickupSound();
	DisableCustomDepth();
}

void AArmorItems::IPickUpItem(ABaseItem* Item, APlayerCharacter* Player)
{
	IPickupInterface::IPickUpItem(Item, Player);
	ParentEquipmentComponent = Player->GetEquipmentComponent();
	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	OwnerPlayer = Player;
	switch (ArmorPart)
	{
	case EPartOfArmor::EPA_Helmet:
		if(Player->GetEquipmentComponent()->ItemsArray[0] == true) break;
		
		this->AttachToComponent(Player->GetMesh(), Rules, FName("HelmetSocket"));
		Player->GetEquipmentComponent()->SetArmorItems(EPartOfArmor::EPA_Helmet, this);
		Player->GetInventorySystemHUD()->EquipArmor(EPartOfArmor::EPA_Helmet);
		SetupArmorCollision();
		break;
	case EPartOfArmor::EPA_Armor:
		if(Player->GetEquipmentComponent()->ItemsArray[1] == true) break;
		
		this->AttachToComponent(Player->GetMesh(), Rules, FName("ArmorSocket"));
		Player->GetEquipmentComponent()->SetArmorItems(EPartOfArmor::EPA_Armor, this);
		Player->GetInventorySystemHUD()->EquipArmor(EPartOfArmor::EPA_Armor);
		SetupArmorCollision();
		break;
	case EPartOfArmor::EPA_Pants:
		if(Player->GetEquipmentComponent()->ItemsArray[2] == true) break;
		
		this->AttachToComponent(Player->GetMesh(), Rules, FName("PantsSocket"));
		Player->GetEquipmentComponent()->SetArmorItems(EPartOfArmor::EPA_Pants, this);
		Player->GetInventorySystemHUD()->EquipArmor(EPartOfArmor::EPA_Pants);
		SetupArmorCollision();
		break;
	}
}

void AArmorItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AArmorItems::GetHit(const FVector& ImpactPoint, AActor* Hitter, const float TakenDamage)
{
	IHitInterface::GetHit(ImpactPoint, Hitter, TakenDamage);
	Durability -= TakenDamage;
	if(Durability <= 0.f)
		BreakArmor();
}

void AArmorItems::BreakArmor()
{
	// 방어구가 깨진다면 HUD도 변경해주어야함
	const FDetachmentTransformRules Rules(EDetachmentRule::KeepRelative, false);
	ParentEquipmentComponent->DeleteArmorItems(ArmorPart);
	OwnerPlayer->GetInventorySystemHUD()->UnEquipArmor(this->ArmorPart);
	this->DetachFromActor(Rules);
	OwnerPlayer = nullptr;
	Destroy();
}

