// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RewardSystem/HUD_Countdown.h"

#include "Components/TextBlock.h"
#include "CustomGameManager/CustomGameInstance.h"

void UHUD_Countdown::NativeConstruct()
{
	Super::NativeConstruct();
	AbsolutelyGameInstance = GetGameInstance();
	CountDown->SetText(FText::AsNumber(Seconds));
	GetWorld()->GetTimerManager().SetTimer(SecondTimer, this, &UHUD_Countdown::DecreaseSecond, 1.f, true);
}

void UHUD_Countdown::DecreaseSecond()
{
	Seconds--;
	if(Seconds >= 0)
	{
		CountDown->SetText(FText::AsNumber(Seconds));
		
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SecondTimer);
		Cast<UCustomGameInstance>(AbsolutelyGameInstance)->GameEnd();
	}
}
