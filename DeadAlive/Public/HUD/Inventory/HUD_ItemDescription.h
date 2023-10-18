// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_ItemDescription.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DEADALIVE_API UHUD_ItemDescription : public UUserWidget
{
	GENERATED_BODY()
public :
	virtual void NativeConstruct() override;
	void SetDescription(const FText& String) const;
private :
	UPROPERTY(meta =(BindWidget))
	UTextBlock* Description;
};
