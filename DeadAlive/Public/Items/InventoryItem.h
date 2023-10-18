#pragma once

#include "CoreMinimal.h"
#include "InventoryBaseItem.h"
#include "Items/BaseItem.h"
#include "InventoryItem.generated.h"

class UHUD_InventoryItemSlot;
class UInventoryItemHUD;
class UInventoryComponent;
class APlayerCharacter;
class UWorld;
class UWeaponInfoWidget;

/*
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Using UMETA(DisplayName = "CanUse"),
	EIT_Edible UMETA(DisplayName = "Edible"),
	EIT_RawMaterial UMETA(DisplayName = "Material"),
	EIT_Equipment UMETA(DisplayName = "Equipment")
};
*/


UCLASS()
class DEADALIVE_API AInventoryItem : public AInventoryBaseItem//, public ABaseItem
{
	GENERATED_BODY()
public :
	AInventoryItem();
	virtual void BeginPlay() override;
	void CreateItemSlotHUD();
	
	/*FORCEINLINE UInventoryComponent* GetOwningInventory() const { return OwningInventory; }
	FORCEINLINE void SetOwningInventory(UInventoryComponent* InventoryComponent) { OwningInventory = InventoryComponent; }*/
	
	/*UPROPERTY(Transient)
	UWorld* MyWorld;*/

	FORCEINLINE UTexture2D* GetItemThumbnail() const { return Thumbnail; }
	FORCEINLINE FText GetItemName() const { return ItemDisplayName; }
	 // FORCEINLINE FText GetItemDescription() const { return ItemDescription; }
	virtual void IPickUpItem(ABaseItem* Item, APlayerCharacter* Player) override;
	FORCEINLINE FName GetNameFromText() const { return FName(ItemDisplayName.ToString()); }
	FORCEINLINE void SetThisItemHUD(UHUD_InventoryItemSlot* HUD) { ItemSlotHUD = HUD; }
	FORCEINLINE UHUD_InventoryItemSlot* GetThisItemHUD() const { return ItemSlotHUD; }

	// FORCEINLINE EItemType GetItemType() const { return InventoryItemType; }

	/*UFUNCTION()
	void DropTheItem();*/
	UFUNCTION()
	virtual void UseItem(APlayerCharacter* Character);

protected:
	// Inventory System
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText UseActionText; // How to use this item? ex) eat, assemble, drop •••
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText ItemDisplayName;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FText ItemDescription;

	UPROPERTY()
	UInventoryComponent* OwningInventory;*/

	UPROPERTY()
	UHUD_InventoryItemSlot* ItemSlotHUD = nullptr;
	

//	void SetItemCollisionToPickUp();
	// void SetItemCollisionToDrop();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	EItemType InventoryItemType;*/

private :
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;*/
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UWeaponAttributes* Attributes;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float HealPoint = 15.f;
	LoadBlueprintClass* LoadBlueprintClass;
};
