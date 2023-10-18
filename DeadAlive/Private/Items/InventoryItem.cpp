#include "Items/InventoryItem.h"
#include "PlayerCharacter.h"
#include "Attributes/WeaponAttributes.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "CustomComponent/InventoryComponent.h"
#include "HUD/Inventory/HUD_InventoryItemSlot.h"
#include "HUD/WeaponInfoWidget.h"

AInventoryItem::AInventoryItem()
{
	/*StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SetRootComponent(StaticMesh);
	SphereCollision->SetupAttachment(RootComponent);
	NoticeSphereCollision->SetupAttachment(RootComponent);
	PickupWidget->SetupAttachment(RootComponent);

	Attributes = CreateDefaultSubobject<UWeaponAttributes>(TEXT("Attributes"));*/
}

void AInventoryItem::CreateItemSlotHUD()
{
	// if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/Item/Weapon/BP_BaseWeapon.BP_BaseWeapon_C")))
	/*FString RelativePath = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSlot");

	if(const auto BlueprintClass = LoadBlueprint->LoadToBlueprintAsset(RelativePath))
	{
		ItemSlotHUD = CreateWidget<UHUD_InventoryItemSlot>(GetWorld(), BlueprintClass);
		ItemSlotHUD->SetParentItem(this);
		SetThisItemHUD(ItemSlotHUD);
	}*/
	if(UObject* BlueprintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSlot.WBP_InventoryItemSlot_C")))
	{
		if(UClass* BluePrintUClass = Cast<UClass>(BlueprintObject))
		{
			ItemSlotHUD = CreateWidget<UHUD_InventoryItemSlot>(GetWorld(), BluePrintUClass);
			ItemSlotHUD->SetParentItem(this);
			SetThisItemHUD(ItemSlotHUD);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("위젯 실패2"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("위젯 실패1"));
	}
	/*if(UObject* BlueprintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSlot.WBP_InventoryItemSlot")))
	{
		UClass* BluePrintUClass = Cast<UClass>(BlueprintObject);
		ItemSlotHUD = CreateWidget<UHUD_InventoryItemSlot>(GetWorld(), BluePrintUClass);
		// ItemSlotHUD->SetParentItem(this);
		SetThisItemHUD(ItemSlotHUD);
	}*/
}

void AInventoryItem::BeginPlay()
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
void AInventoryItem::IPickUpItem(ABaseItem* Item, APlayerCharacter* Player)
{
	Super::IPickUpItem(Item, Player);
	Player->GetInventoryComponent()->AddItem(this);
	
		// SetItemCollisionToPickUp();
}

/*void AInventoryItem::DropTheItem()
{
	SetItemCollisionToDrop();
	this->SetActorLocation(GetOwningInventory()->GetOwningPlayer()->GetActorLocation() + FVector(0.f, 0.f, 30.f));
}*/

void AInventoryItem::UseItem(APlayerCharacter* Character)
{
	GetOwningInventory()->GetOwningPlayer()->GetHit(FVector::Zero(), this, -HealPoint);
}

/*void AInventoryItem::SetItemCollisionToPickUp()
{
	SkeletalComponent->SetVisibility(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NoticeSphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}*/

/*void AInventoryItem::SetItemCollisionToDrop()
{
	SkeletalComponent->SetVisibility(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NoticeSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}*/
