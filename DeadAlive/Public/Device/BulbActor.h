#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulbActor.generated.h"

class UPointLightComponent;
class APointLight;

UCLASS()
class DEADALIVE_API ABulbActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulbActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

protected:
	virtual void BeginPlay() override;

private :
	

};
