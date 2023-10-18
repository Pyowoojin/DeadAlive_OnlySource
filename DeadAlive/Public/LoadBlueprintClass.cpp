#pragma once
#include "LoadBlueprintClass.h"

UClass* LoadBlueprintClass::LoadToBlueprintAsset(FString& BlueprintPath)
{
	/*if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/Item/Weapon/BP_BaseWeapon.BP_BaseWeapon_C")))
	{
		UClass* BluePrintUClass = Cast<UClass>(BluePrintObject);
		auto NewAsset = GetWorld()->SpawnActor<ABaseWeapon>(BluePrintUClass, this->GetActorLocation(), this->GetActorRotation());
	}*/
	if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, *BlueprintPath))
	{
		//UClass* BluePrintUClass = Cast<UClass>(BluePrintObject);
		return Cast<UClass>(BluePrintObject);
	}
	return nullptr;
	/*
	const FString RelativePath = BlueprintPath;

	

	if(const UBlueprint* BlueprintAsset = Cast<UBlueprint>(LoadObject<UBlueprint>(nullptr, *RelativePath)))
	{
		// UE_LOG(LogTemp, Warning, TEXT("에셋 생성 성공"));
		
		if(UClass* BlueprintClass = BlueprintAsset->GeneratedClass)
		{
			return BlueprintClass;
		}
	}
	return nullptr;*/
}
