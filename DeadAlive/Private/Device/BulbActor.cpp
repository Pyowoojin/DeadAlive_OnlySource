#include "Device/BulbActor.h"
#include "Components/PointLightComponent.h"

ABulbActor::ABulbActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PL"));
	SetRootComponent(PointLight);
}
void ABulbActor::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABulbActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

