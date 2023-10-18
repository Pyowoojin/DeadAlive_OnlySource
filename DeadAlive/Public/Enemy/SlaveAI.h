#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlaveAI.generated.h"

class ABaseWeapon;
class UCharacterAttribute;

UCLASS()
class DEADALIVE_API ASlaveAI : public ACharacter
{
	GENERATED_BODY()

public:
	ASlaveAI();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<ABaseWeapon> SlaveWeapon;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime) override;

private :
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterAttribute* CharAttribute;

	
	

};
