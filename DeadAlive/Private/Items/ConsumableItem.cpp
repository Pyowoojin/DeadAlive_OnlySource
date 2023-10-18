// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItem.h"
#include "PlayerCharacter.h"
#include "Attributes/CharacterAttribute.h"

AConsumableItem::AConsumableItem()
{
	
}

void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AConsumableItem::UseItem(APlayerCharacter* Character)
{
	if(Character == nullptr) return;
	
	Super::UseItem(Character);
	Character->GetCharAttribute()->SetHealth(HealthToIncrease);
}
