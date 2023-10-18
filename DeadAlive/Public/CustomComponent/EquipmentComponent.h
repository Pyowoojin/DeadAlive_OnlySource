#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentItemType.h"
#include "EquipmentComponent.generated.h"


class AArmorItems;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADALIVE_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetArmorItems(EPartOfArmor ArmorName, AArmorItems* Item);
	void DeleteArmorItems(EPartOfArmor ArmorName);
	void DamageDistribution(const float TakenDamage);
	bool CanAcceptAttack();
	TArray <bool> ItemsArray = {false, false, false};

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(VisibleAnywhere)
	TSet<AArmorItems*> ArmorContainer;
	
	UPROPERTY(VisibleAnywhere)
	AArmorItems* Helmet;

	UPROPERTY(VisibleAnywhere)
	AArmorItems* Armor;

	UPROPERTY(VisibleAnywhere)
	AArmorItems* Pants;
	
};
