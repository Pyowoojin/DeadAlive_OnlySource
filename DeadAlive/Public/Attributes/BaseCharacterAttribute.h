#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCharacterAttribute.generated.h"

class AEnemyWeapon;
class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADALIVE_API UBaseCharacterAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseCharacterAttribute();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE float GetCurrentHealth() const { return Health; }
	// 그 외 체력 설정
	FORCEINLINE void SetHealth(const int32 Amount) { Health = FMath::Clamp(Health+Amount, -1.f, MaxHealth); }
	// 장비 장착 시에 늘려줄 체력
	FORCEINLINE void AddHealth(const int32 Amount) { Health += Amount; }

protected:
	virtual void BeginPlay() override;
	/* 캐릭터 스탯? */
	UPROPERTY(EditAnywhere, Category = "Character Attributes")
	float Health = 100.f;
	UPROPERTY(EditAnywhere, Category = "Character Attributes")
	float MaxHealth = 100.f;
	
	
private :

		
};
