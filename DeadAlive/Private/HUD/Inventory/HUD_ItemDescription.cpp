// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Inventory/HUD_ItemDescription.h"
#include "Components/TextBlock.h"

void UHUD_ItemDescription::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHUD_ItemDescription::SetDescription(const FText& String) const
{
	Description->SetText(String);
}