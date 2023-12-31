#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "LoadBlueprintClass.h"
#include "BaseItem.generated.h"


class APlayerCharacter;

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Damaged UMETA(DisplayNmae = "Damaged"),
	EIR_Common UMETA(DisplayNmae = "Common"),
	EIR_Uncommon UMETA(DisplayNmae = "Uncommon"),
	EIR_Rare UMETA(DisplayNmae = "Rare"),
	EIR_Legendary UMETA(DisplayNmae = "Legendary"),
	EIR_Max UMETA(DisplayNmae = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	// 바닥에 떨군 상태
	EIS_Free UMETA(DisplayNmae = "Free"),
	// 플레이어가 가지고는 있지만 장착하지 않은 상태
	EIS_UnEquipped UMETA(DisplayNmae = "UnEquipped"),
	// 손에 들고 있는 상태
	EIS_Equipped UMETA(DisplayNmae = "Equipped")
};

class UWeaponInfoWidget;
class USkeletalMeshComponent;
class USphereComponent;
class UPrimitiveComponent;
class UWeaponAttributes;
class USoundBase;
class UGameplayStatics;
class UParticleSystem;
class UWidgetComponent;
class UTexture2D;

UCLASS(Blueprintable)
class DEADALIVE_API ABaseItem : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void Tick(float DeltaTime) override;
	virtual void IPickUpItem(ABaseItem* Item, APlayerCharacter* Player) override;

protected:
	virtual void BeginPlay() override;

	// 희귀도 기반으로 별의 개수를 Active시킴
	void SetActiveStarts();

	// 오버랩 함수들
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void NoticeRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void NoticeRangeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 플레이어가 아이템을 볼 때 팝업으로 띄워줄 위젯 -> 부모
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* PickupWidget;

	// N성급 무기 -> 부모
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemRarity ItemRarity = EItemRarity::EIR_Common;

	// 아이템 상태 Enum -> 부모
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemState ItemState = EItemState::EIS_Free;

	// - 부모
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	TArray<bool> ActiveStarts;

	// 아이템 스켈레탈 메시
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalComponent;

	// 무기를 줍거나 특성을 볼 때 사용되는 콜리전
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	// 무기 특성 표시가 가능한 범위를 나타내는 Sphere collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoticeSphereCollision;

	// 블루프린트 에셋 로드
	LoadBlueprintClass* LoadBlueprint;

	UPROPERTY()
	UWeaponInfoWidget* WeaponInfo = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundWave* PlayingEquipSound;

public :
	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	FORCEINLINE void SetItemState(EItemState State ) { ItemState = State; }
	FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalComponent; }

	// 커스텀 뎁스 활성화, 비활성화
	FORCEINLINE void EnableCustomDepth() const { if(SkeletalComponent) SkeletalComponent->SetRenderCustomDepth(true); }
	FORCEINLINE void DisableCustomDepth() const { if(SkeletalComponent) SkeletalComponent->SetRenderCustomDepth(false);}
	
	void ThrowTheWeapon();
	void SetCollisionDisable();
	void SetCollisionEnable();
	void PlayPickupSound();

private :
	
};