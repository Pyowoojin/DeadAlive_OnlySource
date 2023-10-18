#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ASlaveAI;
class UHUD_ItemDescription;
class AInventoryBaseItem;
class UHUD_ItemSelectionMenu;
class LoadBlueprintClass;
class UHUD_InventorySystem;
class UInventoryItemHUD;
class APlayerCharacter;
class UInventorySystemHUD;
class AInventoryItem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryUpdated, AInventoryItem*, NewItem, bool, bAddOrRemove);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectionChange);

USTRUCT()
struct FItemInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	AInventoryBaseItem* Item = nullptr;

	UPROPERTY()
	int32 Count = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADALIVE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE APlayerCharacter* GetOwningPlayer() const { return OwningPlayer;}
	FORCEINLINE UHUD_ItemDescription* GetItemDescription() const { return ItemDescription; }

	FSelectionChange FSelectionChangeDel;

	UFUNCTION()
	bool AddItem(AInventoryBaseItem* ItemToAdd);
	void DeleteItemFromArray(AInventoryBaseItem* ItemToRemove);
	bool RemoveItem(AInventoryBaseItem* ItemToRemove);
	bool DropInventoryItem(AInventoryBaseItem* ItemToDrop);
	bool CheckCanCombination(AInventoryItem* ItemToCombi, const FItemInfo& ItemInfo);
	void Combi_Item(AInventoryItem* ItemToCombi);
	void UseItem(AInventoryBaseItem* ItemToUse);
	FORCEINLINE UHUD_ItemSelectionMenu* GetItemSelectionInstance() { return ItemSelectionInstance; };
	UFUNCTION()
	void CreateInventorySystemInstance();

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray <AInventoryBaseItem*> DefaultItem;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FInventoryUpdated InventoryUpdateDelegate;

	UPROPERTY(EditDefaultsOnly)
	AInventoryBaseItem* RetItem;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray <AInventoryBaseItem*> Items;

	LoadBlueprintClass* LBC;

	/* 새로 가져온거 */
	
	void CreateSelectionHUD();
	void CreateDescriptionHUD();
	UFUNCTION()
	void CloseSelection();

protected:
	virtual void BeginPlay() override;

private :

	// 컴포넌트 내의 SystemHUDInstance
	/*UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	UInventorySystemHUD* InventorySystemHUDInstance;*/

	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	UHUD_InventorySystem* InventorySystemHUDInstance;
	
	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* OwningPlayer;

	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	int8 MaximumItemCount = 20;

	UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TMap<FName, FItemInfo> DataTable;

	FItemInfo TempItemInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<AInventoryBaseItem> ItemReference;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UHUD_ItemSelectionMenu* ItemSelectionInstance;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UHUD_ItemDescription* ItemDescription;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSoftClassPtr<UHUD_ItemSelectionMenu> ItemSelectionInstanceClassPtr;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSoftClassPtr<UHUD_ItemDescription> ItemDescriptionPtr;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSoftClassPtr<AInventoryItem> Bandage;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSoftClassPtr<AInventoryItem> Slaves;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSoftClassPtr<ASlaveAI> SlavesCharacter;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TArray<TSoftClassPtr<AInventoryItem>> InventoryItems;

	
	

	void ItemCombinationEquation();
	
};