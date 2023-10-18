#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "EnemyWeapon.generated.h"

class UBoxComponent;
class AEnemyWeapon;

UCLASS()
class DEADALIVE_API AEnemyWeapon : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:
	AEnemyWeapon();
	virtual void Tick(float DeltaTime) override;
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	UFUNCTION()
	void DamageInstigate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void DamageApply(IHitInterface* AppliedActor, AActor* Hitter);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void ResultOfSlash(FHitResult& HitResult);
	void SetWeaponNoCollision();
	void SetWeaponCollision();
	FORCEINLINE float GetWeaponDamage() const { return WeaponDamage; }

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Temporary;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
	USceneComponent* TraceStart;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* TraceEnd;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> IgnoreActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float WeaponDamage = 5.f;

};
