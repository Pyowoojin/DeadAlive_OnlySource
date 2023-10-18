#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "InventoryBaseItem.generated.h"

class UWeaponAttributes;
class UHUD_InventoryItemSlot;
class UInventoryComponent;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Using UMETA(DisplayName = "CanUse"),
	EIT_Edible UMETA(DisplayName = "Edible"),
	EIT_RawMaterial UMETA(DisplayName = "Material"),
	EIT_Equipment UMETA(DisplayName = "Equipment")
};

UCLASS()
class DEADALIVE_API AInventoryBaseItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	AInventoryBaseItem();
	
	FORCEINLINE UInventoryComponent* GetOwningInventory() const { return OwningInventory; }
	FORCEINLINE void SetOwningInventory(UInventoryComponent* InventoryComponent) { OwningInventory = InventoryComponent; }
	
	UPROPERTY(Transient)
	UWorld* MyWorld;

	
	UFUNCTION()
	virtual void IPickUpItem(ABaseItem* Item, APlayerCharacter* Player) override;
	/*
	void CreateItemSlotHUD();
	FORCEINLINE FName GetNameFromText() const { return FName(ItemDisplayName.ToString()); }
	FORCEINLINE void SetThisItemHUD(UHUD_InventoryItemSlot* HUD) { ItemSlotHUD = HUD; }
	FORCEINLINE UHUD_InventoryItemSlot* GetThisItemHUD() const { return ItemSlotHUD; }
	FORCEINLINE UTexture2D* GetItemThumbnail() const { return Thumbnail; }
	FORCEINLINE FText GetItemName() const { return ItemDisplayName; }
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }
	UFUNCTION()
	virtual void UseItem(APlayerCharacter* Character);
	*/
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }
	FORCEINLINE EItemType GetItemType() const { return InventoryItemType; }

	UFUNCTION()
	void DropTheItem();

protected:
	// Inventory System

	virtual void BeginPlay() override;

	UPROPERTY()
	UInventoryComponent* OwningInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UWeaponAttributes* Attributes;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText UseActionText; // How to use this item? ex) eat, assemble, drop •••
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText ItemDisplayName;
	UPROPERTY()
	UHUD_InventoryItemSlot* ItemSlotHUD = nullptr;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText ItemDescription;
	
	/*void SetItemCollisionToPickUp();*/
	void SetItemCollisionToDrop();
	void SetItemCollisionToPickUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	EItemType InventoryItemType;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;*/

private :

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float HealPoint = 15.f;	*/

};