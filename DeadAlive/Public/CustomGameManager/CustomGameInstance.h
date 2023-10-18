// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEADALIVE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintNativeEvent)
	void GameEnd();
	UFUNCTION(BlueprintNativeEvent)
	void GameRestart();
	UFUNCTION(BlueprintNativeEvent)
	void GameClear();
};
