#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterAttribute.h"
#include "Components/ActorComponent.h"
#include "EnemyAttribute.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADALIVE_API UEnemyAttribute : public UBaseCharacterAttribute
{
	GENERATED_BODY()

public:	
	UEnemyAttribute();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetEquippedWeapon(AEnemyWeapon* Item) { EnemyWeapon = Item; }
	FORCEINLINE AEnemyWeapon* GetEquippedWeapon() const { return EnemyWeapon; }
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	AEnemyWeapon* EnemyWeapon = nullptr;
};
