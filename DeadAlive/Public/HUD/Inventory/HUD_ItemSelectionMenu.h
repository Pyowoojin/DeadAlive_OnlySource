// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_ItemSelectionMenu.generated.h"

class AInventoryBaseItem;
class UCanvasPanelSlot;
class UCanvasPanel;
class AInventoryItem;
class UButton;
class UTextBlock;

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam()

UCLASS()
class DEADALIVE_API UHUD_ItemSelectionMenu : public UUserWidget
{
	GENERATED_BODY()

public :
	void ItemSelectionInitialization();
	virtual void NativeConstruct() override;
	UFUNCTION()
	void UseButtonFunction();
	UFUNCTION()
	void CombinationFunction();
	UFUNCTION()
	void DropButtonFunction();

	void SetButtonClickable();

	void SetParentItem(AInventoryBaseItem* Item);
	FORCEINLINE AInventoryBaseItem* GetParentItem() { return ParentItem; }
	
private :
	UPROPERTY(meta =(BindWidget))
	UCanvasPanel* CanvasPanel;
	
	UPROPERTY(meta =(BindWidget))
	UButton* UseButton;

	UPROPERTY(meta =(BindWidget))
	UButton* CombinationButton;

	UPROPERTY(meta =(BindWidget))
	UButton* DropButton;

	UPROPERTY()
	AInventoryBaseItem* ParentItem;
};
