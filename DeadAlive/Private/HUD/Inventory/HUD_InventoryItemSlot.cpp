#include "HUD/Inventory/HUD_InventoryItemSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "HUD/Inventory/HUD_ItemSelectionMenu.h"
#include "Items/InventoryItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CustomComponent/InventoryComponent.h"
#include "HUD/Inventory/HUD_ItemDescription.h"

void UHUD_InventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSlotInitialize();

	ItemButton->OnHovered.AddDynamic(this, &UHUD_InventoryItemSlot::WhenHoverTheButton);
	ItemButton->OnUnhovered.AddDynamic(this, &UHUD_InventoryItemSlot::WhenUnHoverTheButton);
	ItemButton->OnClicked.AddDynamic(this, &UHUD_InventoryItemSlot::WhenClicked);
}

void UHUD_InventoryItemSlot::WhenHoverTheButton()
{
	if(auto ItemDescription = ParentItem->GetOwningInventory()->GetItemDescription())
	{
		ItemDescription->SetDescription(ParentItem->GetItemDescription());
		const FVector2D MousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		ItemDescription->SetPositionInViewport(MousePoint, false);
		ItemDescription->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUD_InventoryItemSlot::WhenClicked()
{
	UE_LOG(LogTemp, Error, TEXT("웬 클릭"));
	// 로그 확인 여기가 문제임 안 받아와져요
	if(const auto ItemSelection = GetParentItem()->GetOwningInventory()->GetItemSelectionInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("셀렉션 존재"));
		if(ItemSelection->GetVisibility() == ESlateVisibility::Visible)
		{
			UE_LOG(LogTemp, Error, TEXT("비지블"));
			ItemSelection->SetVisibility(ESlateVisibility::Hidden);			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("히든"));
			// 브로드캐스트
			ItemSelection->SetParentItem(ParentItem);
			ItemSelection->SetButtonClickable();
			GetParentItem()->GetOwningInventory()->FSelectionChangeDel.Broadcast();
			const FVector2D MousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
			ItemSelection->SetPositionInViewport(MousePoint, false);
			ItemSelection->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("셀렉션 존재 안 함"));
	}
}

/*
void UHUD_InventoryItemSlot::CloseSelection()
{
	if(ItemSelection)
	{
		ItemSelection->SetVisibility(ESlateVisibility::Hidden);
	}
}
*/

void UHUD_InventoryItemSlot::WhenUnHoverTheButton()
{
	if(auto ItemDescription = ParentItem->GetOwningInventory()->GetItemDescription())
	{
		ItemDescription->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHUD_InventoryItemSlot::SetParentItem(AInventoryItem* TargetItem)
{
	ParentItem = TargetItem;
}

AInventoryBaseItem* UHUD_InventoryItemSlot::GetParentItem() const
{
	return ParentItem;
}

void UHUD_InventoryItemSlot::ItemSlotInitialize() const
{
	if(ParentItem->GetItemType() == EItemType::EIT_Equipment) return ;
	
	if(const AInventoryItem* ParentItem_Casting = Cast<AInventoryItem>(ParentItem))
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ParentItem_Casting->GetItemThumbnail());

		if(ItemName)
		{
			ItemName->SetText(ParentItem_Casting->GetItemName());
		}

		if(ItemThumbnail)
		{
			ItemThumbnail->SetBrush(Brush);
		}
	}
}



/*void UHUD_InventoryItemSlot::CreateSelectionHUD()
{
	const FString RelativePath = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection");

	if(const UBlueprint* BlueprintAsset = Cast<UBlueprint>(LoadObject<UBlueprint>(nullptr, *RelativePath)))
	{
		if(UClass* BlueprintClass = BlueprintAsset->GeneratedClass)
		{
			ItemSelection = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), BlueprintClass);
			if(ItemSelection)
			{
				ItemSelection->SetParentItem(GetParentItem());
				UE_LOG(LogTemp, Warning, TEXT("셀렉션 위젯 생성 완료 및 델리게이트 바인딩 완료"));
				ItemSelection->AddToViewport(0);
				ItemSelection->SetVisibility(ESlateVisibility::Hidden);
				GetParentItem()->GetOwningInventory()->FSelectionChangeDel.AddDynamic(this, &UHUD_InventoryItemSlot::CloseSelection);
			}
		}
	}
}*/