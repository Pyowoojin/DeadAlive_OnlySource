#include "Items/InventoryBaseItem.h"
#include "PlayerCharacter.h"
#include "Attributes/WeaponAttributes.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "CustomComponent/InventoryComponent.h"
#include "Items/InventoryItem.h"
#include "HUD/WeaponInfoWidget.h"

AInventoryBaseItem::AInventoryBaseItem()
{
	Attributes = CreateDefaultSubobject<UWeaponAttributes>(TEXT("Attributes"));
}

/*void AInventoryBaseItem::CreateItemSlotHUD()
{
	const FString RelativePath = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSlot");

	if(const auto BlueprintClass = LoadBlueprint->LoadToBlueprintAsset(RelativePath))
	{
		ItemSlotHUD = CreateWidget<UHUD_InventoryItemSlot>(GetWorld(), BlueprintClass);
		ItemSlotHUD->SetParentItem(this);
		SetThisItemHUD(ItemSlotHUD);
	}
}*/

void AInventoryBaseItem::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponInfo)
	{
		WeaponInfo = Cast<UWeaponInfoWidget>(PickupWidget->GetUserWidgetObject());
		WeaponInfo->SetItemName(Attributes->GetItemName());
		WeaponInfo->SetAmmo(1);
	}
	SetActiveStarts();
}

// 인터페이스를 호출하면 인벤토리로 들어감
void AInventoryBaseItem::IPickUpItem(ABaseItem* Item, APlayerCharacter* Player)
{
	Super::IPickUpItem(Item, Player);
	SetItemCollisionToPickUp();
	// Player->GetInventoryComponent()->AddItem(this);
	/*if(Player->GetInventoryComponent()->AddItem(this))
	{
		// SetItemCollisionToPickUp();
	}*/
}

void AInventoryBaseItem::DropTheItem()
{
	// this->SetActorLocation(GetOwningInventory()->GetOwningPlayer()->GetActorLocation() + FVector(0.f, 0.f, 30.f), false, nullptr, ETeleportType::TeleportPhysics);
	this->SetActorLocation(GetOwningInventory()->GetOwningPlayer()->GetActorLocation() + FVector(0.f, 0.f, 30.f));
	SetItemCollisionToDrop();
	EnableCustomDepth();
}

void AInventoryBaseItem::SetItemCollisionToPickUp()
{
	SkeletalComponent->SetSimulatePhysics(false);
	SkeletalComponent->SetVisibility(false);
	SkeletalComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NoticeSphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInventoryBaseItem::SetItemCollisionToDrop()
{
	SkeletalComponent->SetVisibility(true);
	SkeletalComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NoticeSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SkeletalComponent->SetSimulatePhysics(true);
}