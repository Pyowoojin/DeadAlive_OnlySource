#include "HUD/Inventory/HUD_ItemSelectionMenu.h"
#include "Components/Button.h"
#include "CustomComponent/InventoryComponent.h"
#include "Items/InventoryItem.h"

// 아이템 마다 다 생성하는게 아니라 1개만 생성하고 그걸 돌려서 쓰자.
// 다른 아이템을 클릭하면 기존에 연결은 종료시키고 새로운 아이템 정보로 다시 가져와야함 
void UHUD_ItemSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ItemSelectionInitialization();
	SetButtonClickable();
}

void UHUD_ItemSelectionMenu::UseButtonFunction()
{
	ParentItem->GetOwningInventory()->UseItem(ParentItem);
}

void UHUD_ItemSelectionMenu::CombinationFunction()
{
	if(AInventoryItem* Item = Cast<AInventoryItem>(ParentItem))
	{
		ParentItem->GetOwningInventory()->Combi_Item(Item);
	}
}

void UHUD_ItemSelectionMenu::DropButtonFunction()
{
	ParentItem->GetOwningInventory()->DropInventoryItem(ParentItem);
}

// 조합해야 하는 아이템은 사용 버튼 제거, 바로 사용할 수 있는 아이템은 조합 버튼 제거
void UHUD_ItemSelectionMenu::SetButtonClickable()
{
	if(ParentItem == nullptr) return;
	
	if(ParentItem->GetItemType() == EItemType::EIT_RawMaterial)
	{
		CombinationButton->SetIsEnabled(true);
		UseButton->SetIsEnabled(false);
	}
	else if(ParentItem->GetItemType() == EItemType::EIT_Using)
	{
		UseButton->SetIsEnabled(true);
		CombinationButton->SetIsEnabled(false);
	}
}

void UHUD_ItemSelectionMenu::SetParentItem(AInventoryBaseItem* Item)
{
	ParentItem = Item;
}

void UHUD_ItemSelectionMenu::ItemSelectionInitialization()
{
	UseButton->IsFocusable = false;
	CombinationButton->IsFocusable = false;
	DropButton->IsFocusable = false;
	UseButton->OnClicked.AddDynamic(this, &UHUD_ItemSelectionMenu::UseButtonFunction);
	DropButton->OnClicked.AddDynamic(this, &UHUD_ItemSelectionMenu::DropButtonFunction);
	CombinationButton->OnClicked.AddDynamic(this, &UHUD_ItemSelectionMenu::CombinationFunction);
	UseButton->SetIsEnabled(false);
	CombinationButton->SetIsEnabled(false);
	DropButton->SetIsEnabled(true);
}
