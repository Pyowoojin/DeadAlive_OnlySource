#include "Attributes/BaseCharacterAttribute.h"

UBaseCharacterAttribute::UBaseCharacterAttribute()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBaseCharacterAttribute::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBaseCharacterAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

