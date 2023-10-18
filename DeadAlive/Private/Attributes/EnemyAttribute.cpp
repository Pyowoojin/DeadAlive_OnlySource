#include "Attributes/EnemyAttribute.h"

UEnemyAttribute::UEnemyAttribute()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEnemyAttribute::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

