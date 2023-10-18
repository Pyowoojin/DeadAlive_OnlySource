#pragma once

#include "CoreMinimal.h"
#include "Items/InventoryItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class DEADALIVE_API AConsumableItem : public AInventoryItem
{
	GENERATED_BODY()

public :
	virtual void UseItem(APlayerCharacter* Character) override;
	AConsumableItem();
	virtual void BeginPlay() override;
protected:

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float HealthToIncrease = 15.f;
	
};
