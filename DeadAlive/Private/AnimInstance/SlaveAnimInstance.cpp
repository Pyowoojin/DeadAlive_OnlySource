#include "AnimInstance/SlaveAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USlaveAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	SlaveCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if(SlaveCharacter)
	{
		CharMovement = SlaveCharacter->GetCharacterMovement();
	}
}


void USlaveAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(CharMovement)
	{
		Direction = CalculateDirection(CharMovement->Velocity, SlaveCharacter->GetActorForwardVector().Rotation());
	}
}
