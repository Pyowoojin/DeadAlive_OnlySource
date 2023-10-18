#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ATargetPoint;
class USphereComponent;
class AEnemyCharacter;

UCLASS()
class DEADALIVE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void InitSpawner();
	void OnEnemyDead(AEnemyCharacter* Enemy);
	void SpawnFromObjectPool(const AActor* SpawnLocation, const FVector& TargetLocation);
	// SpawnCount, SpawnLocation, TargetPoint
	void SpawnEnemy(const int32 SpawnCount, const AActor* SpawnLocation, const FVector& TargetLocation, float SpawnDelay = 0.1f, int32 SpawnCycle = 1);
	

	UPROPERTY(EditAnywhere)
	int32 DeathCount = 0;

	FTimerHandle SpawnTimer;
	FTimerHandle StopSpawnTimer;
	void StopSpawnTimerFunc();
	FTimerDelegate SpawnTimerDelegate;
	
	/*UFUNCTION()
	void SpawnEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);*/
	UFUNCTION(BlueprintCallable)
	void EnemyWork();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TSubclassOf<AEnemyCharacter> PooledObjectClass;

	UPROPERTY(EditAnywhere, Category = "Custom")
	TArray<AEnemyCharacter*> EnemyObjectPool;

	UPROPERTY(EditAnywhere)
	int32 MaxEnemyObjectsSize = 0;
	UPROPERTY(EditAnywhere)
	int32 CurrentEnemyObjectPoolSize = 0;

	UPROPERTY(EditAnywhere)
	AActor* DestinationActor;

	UPROPERTY(EditAnywhere)
	AActor* SpawnLocationActor;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsClear = false;


private :
	void WaveStart();
	void WaveStop();
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* WaveSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent;
	
	void CreateEnemy(const int32 SpawnCount);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyCharacter> EnemyClass;
	
};