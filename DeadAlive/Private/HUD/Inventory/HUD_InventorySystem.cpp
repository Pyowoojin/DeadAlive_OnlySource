#include "HUD/Inventory/HUD_InventorySystem.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "HUD/Inventory/HUD_InventoryItemSlot.h"
#include "Items/InventoryItem.h"


void UHUD_InventorySystem::RefreshItemInventory(AInventoryItem* NewItem, bool bAdd)
{
	// 아이템 추가하는 경우
	if(bAdd)
	{
		// UE_LOG(LogTemp, Warning, TEXT("아이템 추가"));
		NewItem->CreateItemSlotHUD();
		WrapBox->AddChildToWrapBox(NewItem->GetThisItemHUD());
		NewItem->GetThisItemHUD()->AddToViewport(0);
	}

	// 아이템 삭제하는 경우
	else if(!bAdd)
	{
		// UE_LOG(LogTemp, Warning, TEXT("아이템 삭제"));
		NewItem->GetThisItemHUD()->RemoveFromParent();
		// NewItem->GetOwningInventory()->InventoryUpdateDelegate.Broadcast();
	}
}

void UHUD_InventorySystem::NativeConstruct()
{
	Super::NativeConstruct();
	HelmetButton->OnClicked.AddDynamic(this, &UHUD_InventorySystem::HelmetButtonClicked);
	HelmetButton->OnHovered.AddDynamic(this, &UHUD_InventorySystem::HelmetButtonClicked);
	ArmorButton->OnClicked.AddDynamic(this, &UHUD_InventorySystem::ArmorButtonClicked);
	ArmorButton->OnHovered.AddDynamic(this, &UHUD_InventorySystem::ArmorButtonClicked);
	BootsButton->OnClicked.AddDynamic(this, &UHUD_InventorySystem::BootsButtonClicked);
	BootsButton->OnHovered.AddDynamic(this, &UHUD_InventorySystem::BootsButtonClicked);
}

void UHUD_InventorySystem::EquipArmor(EPartOfArmor ArmorType)
{
	switch(ArmorType)
	{
	case EPartOfArmor::EPA_Helmet:
		HelmetImage->SetVisibility(ESlateVisibility::Visible);
		break;

	case EPartOfArmor::EPA_Armor:
		ArmorImage->SetVisibility(ESlateVisibility::Visible);
		break;

	case EPartOfArmor::EPA_Pants :
		BootsImage->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UHUD_InventorySystem::UnEquipArmor(EPartOfArmor ItemType)
{
	switch(ItemType)
	{
	case EPartOfArmor::EPA_Helmet:
		HelmetImage->SetVisibility(ESlateVisibility::Hidden);
		break;

	case EPartOfArmor::EPA_Armor:
		ArmorImage->SetVisibility(ESlateVisibility::Hidden);
		break;

	case EPartOfArmor::EPA_Pants :
		BootsImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}

void UHUD_InventorySystem::HelmetButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("헬멧 클릭"));
}

void UHUD_InventorySystem::ArmorButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("아머 클릭"));
}

void UHUD_InventorySystem::BootsButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("부츠 클릭"));
}
