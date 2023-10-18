#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "EquipmentItemType.h"
#include "InventoryBaseItem.h"
#include "Interfaces/HitInterface.h"
#include "ArmorItems.generated.h"


class UEquipmentComponent;

UCLASS()
class DEADALIVE_API AArmorItems : public AInventoryBaseItem, public IHitInterface// public ABaseItem, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	AArmorItems();
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter, const float TakenDamage) override;
	void BreakArmor();
	
	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* OwnerPlayer = nullptr;

	UPROPERTY(EditAnywhere)
	EPartOfArmor ArmorPart;

protected:
	virtual void BeginPlay() override;
	void SetupArmorCollision();
	virtual void IPickUpItem(ABaseItem* Item, APlayerCharacter* Player) override;

private :
	UPROPERTY(EditAnywhere)
	float Durability = 30.f;

	UPROPERTY()
	UEquipmentComponent* ParentEquipmentComponent;
};
