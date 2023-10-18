// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentItemType.h"
#include "HUD_InventorySystem.generated.h"

class UOverlay;
class UImage;
class AInventoryItem;
class UButton;
class UWrapBox;
/**
 * 
 */
UCLASS()
class DEADALIVE_API UHUD_InventorySystem : public UUserWidget
{
	GENERATED_BODY()

public :

	UFUNCTION()
	void RefreshItemInventory(AInventoryItem* NewItem, bool bAdd);
	virtual void NativeConstruct() override;
	void EquipArmor(EPartOfArmor ItemType);
	void UnEquipArmor(EPartOfArmor ItemType);

private :
	UPROPERTY(meta =(BindWidget))
	UWrapBox* WrapBox;

	UPROPERTY(meta =(BindWidget))
	UOverlay* HelmetOverlay;

	UPROPERTY(meta =(BindWidget))
	UImage* HelmetImage;

	UPROPERTY(meta =(BindWidget))
	UButton* HelmetButton;

	UPROPERTY(meta =(BindWidget))
	UOverlay* ArmorOverlay;

	UPROPERTY(meta =(BindWidget))
	UImage* ArmorImage;

	UPROPERTY(meta =(BindWidget))
	UButton* ArmorButton;

	UPROPERTY(meta =(BindWidget))
	UOverlay* BootsOverlay;

	UPROPERTY(meta =(BindWidget))
	UImage* BootsImage;

	UPROPERTY(meta =(BindWidget))
	UButton* BootsButton;

	UFUNCTION()
	void HelmetButtonClicked();
	UFUNCTION()
	void ArmorButtonClicked();
	UFUNCTION()
	void BootsButtonClicked();
	
};
