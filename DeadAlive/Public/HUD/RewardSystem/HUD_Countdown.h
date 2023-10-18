// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Countdown.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DEADALIVE_API UHUD_Countdown : public UUserWidget
{
	GENERATED_BODY()
public :
	FTimerHandle SecondTimer;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void DecreaseSecond();
	
	UPROPERTY(meta =(BindWidget))
	UTextBlock* CountDown;

	UPROPERTY(VisibleAnywhere)
	int32 Seconds = 120;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	UGameInstance* AbsolutelyGameInstance;
};
