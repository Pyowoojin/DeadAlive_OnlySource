// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Items/BaseItem.h"
#include "RewardWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class LoadBlueprintClass;

USTRUCT(BlueprintType)
struct FRewardDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Custom")
	FText SelectionName;
	UPROPERTY(EditAnywhere, Category = "Custom")
	FText Description;
	UPROPERTY(EditAnywhere, Category = "Custom")
	UTexture2D* SelectionImage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Custom")
	FString LoadPathString;
	UPROPERTY(EditAnywhere, Category = "Custom")
	FString ExtraPath;
	UPROPERTY(EditAnywhere, Category = "Custom")
	int32 Count = 0;
	UPROPERTY(EditAnywhere, Category = "Custom")
	TSoftClassPtr<ABaseItem> InvenItem;
	
};
UCLASS()
class DEADALIVE_API URewardWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	UDataTable* RewardTableAsset;

	void Test();
	void Initialization();
	void SelectInputOnly();
	void SetViewOfWidgets();
	void DistributeItems(const FRewardDataTableRow& Info);
	void GameInputOnly();

protected:

	
private :
	UPROPERTY(meta =(BindWidget))
	UTextBlock* LeftSelectionName;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* LeftDescriptionText;

	UPROPERTY(meta =(BindWidget))
	UImage* LeftImage;

	UPROPERTY(meta =(BindWidget))
	UButton* LeftButton;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* RightSelectionName;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* RightDescriptionText;

	UPROPERTY(meta =(BindWidget))
	UImage* RightImage;

	UPROPERTY(meta =(BindWidget))
	UButton* RightButton;

	LoadBlueprintClass* LoadBlueprintClass;

	TArray <FRewardDataTableRow*> RewardArray;

	FRewardDataTableRow* LeftInfo;

	FRewardDataTableRow* RightInfo;

	UFUNCTION()
	void ClickLeftButton();
	UFUNCTION()
	void ClickRightButton();
	
};
