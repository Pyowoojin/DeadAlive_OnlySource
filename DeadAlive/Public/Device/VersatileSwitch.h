#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "VersatileSwitch.generated.h"

class AEnemySpawner;
class ATargetPoint;
class ABulbActor;
class UBoxComponent;
class AEnemyCharacter;

UCLASS()
class DEADALIVE_API AVersatileSwitch : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AVersatileSwitch();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void InteractWithThisActor() override;

	UFUNCTION()
	void TestFunc();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Custom")
	int32 EnemySpawnCount = 0;

	UPROPERTY(EditAnywhere, Category = "Custom")
	float EnemySpawnDelay = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Custom")
	int32 EnemySpawnCycle = 1;

	UPROPERTY(EditAnywhere, Category = "Custom")
	AActor* EnemyTargetPoint;

	UPROPERTY(EditAnywhere)
	bool bIsActive = false;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TArray <ABulbActor*> BulbArray;

	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TArray <AEnemyCharacter*> EnemyArray;

	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	AActor* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	AEnemySpawner* Spawner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	AEnemySpawner* Spawner2;
};
