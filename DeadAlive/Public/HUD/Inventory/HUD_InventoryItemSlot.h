#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_InventoryItemSlot.generated.h"

class AInventoryBaseItem;
class UHUD_ItemDescription;
class UWrapBox;
class UHUD_ItemSelectionMenu;
class UButton;
class UTextBlock;
class UImage;
class AInventoryItem;

UCLASS()
class DEADALIVE_API UHUD_InventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()

public :
	void SetParentItem(AInventoryItem* TargetItem);
	AInventoryBaseItem* GetParentItem() const;
	// void CreateDescriptionHUD();
	// void CreateSelectionHUD();
	void ItemSlotInitialize() const;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void WhenHoverTheButton();
	UFUNCTION()
	void WhenUnHoverTheButton();
	UFUNCTION()
	void WhenClicked();
	
private :

	UPROPERTY()
	AInventoryBaseItem* ParentItem;

	UPROPERTY(meta =(BindWidget))
	UImage* ItemThumbnail;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta =(BindWidget))
	UButton* ItemButton;

	/*UPROPERTY()
	UHUD_ItemDescription* ItemDescription;*/

	/*UPROPERTY()
	UHUD_ItemSelectionMenu* ItemSelection;*/
};
