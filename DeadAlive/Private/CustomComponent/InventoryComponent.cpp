#include "CustomComponent/InventoryComponent.h"
#include "PlayerCharacter.h"
#include "HUD/Inventory/HUD_InventorySystem.h"
#include "Enemy/SlaveAI.h"
#include "HUD/Inventory/HUD_ItemDescription.h"
#include "HUD/Inventory/HUD_ItemSelectionMenu.h"
#include "Items/InventoryItem.h"
#include "Items/InventoryBaseItem.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayer = Cast<APlayerCharacter>(GetOwner());

	// UE_LOG(LogTemp, Warning, TEXT("인벤토리 컴퍼넌트 비긴플레이"));
	CreateInventorySystemInstance();

	for(const auto& Item: DefaultItem)
	{
		AddItem(Item);
	}
	ItemCombinationEquation();
	CreateSelectionHUD();
	CreateDescriptionHUD();
}

void UInventoryComponent::ItemCombinationEquation()
{
	/*if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/Item/Weapon/BP_BaseWeapon.BP_BaseWeapon_C")))
	{
		UClass* BluePrintUClass = Cast<UClass>(BluePrintObject);
		auto NewAsset = GetWorld()->SpawnActor<ABaseWeapon>(BluePrintUClass, this->GetActorLocation(), this->GetActorRotation());
	}*/
	// 보상으로 줄 아이템

	if(!Bandage.IsNull() && !Slaves.IsNull())
	{
		if(UClass* BlueprintClass = Bandage.LoadSynchronous())
		{
			TempItemInfo.Item = GetWorld()->SpawnActor<AInventoryItem>(BlueprintClass);
			// 조합에 필요한 아이템 개수
			TempItemInfo.Count = 2;
			// 조합에 필요한 아이템
			DataTable.Add(FName("Fabric"), TempItemInfo);
		}

		if(UClass* BlueprintClass = Slaves.LoadSynchronous())
		{
			TempItemInfo.Item = GetWorld()->SpawnActor<AInventoryItem>(BlueprintClass);
			// 조합에 필요한 아이템 개수
			TempItemInfo.Count = 8;
			DataTable.Add(FName("metal"), TempItemInfo);
		}
	}
	
	/*FString LoadPath = TEXT("/Game/Blueprint/Item/InventoryItem/BP_Bandage.BP_Bandage_C");
	TempItemInfo.Item = Cast<AInventoryBaseItem>(GetWorld()->SpawnActor<AInventoryItem>(LBC->LoadToBlueprintAsset(LoadPath)));
	// 조합에 필요한 아이템 개수
	TempItemInfo.Count = 2;
	// 조합에 필요한 아이템
	DataTable.Add(FName("Fabric"), TempItemInfo);

	FString LoadPath2 = TEXT("/Game/Blueprint/Item/InventoryItem/BP_Slaves.BP_Slaves_C");
	TempItemInfo.Item = Cast<AInventoryBaseItem>(GetWorld()->SpawnActor<AInventoryItem>(LBC->LoadToBlueprintAsset(LoadPath2)));
	TempItemInfo.Count = 2;
	DataTable.Add(FName("metal"), TempItemInfo);*/
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UInventoryComponent::AddItem(AInventoryBaseItem* ItemToAdd)
{
	CreateInventorySystemInstance();
	if(ItemToAdd && Items.Num() < MaximumItemCount)
	{
		// UE_LOG(LogTemp, Warning, TEXT("애드 아이템"));
		
		Items.Add(ItemToAdd);
		ItemToAdd->SetOwningInventory(this);
		ItemToAdd->MyWorld = ItemToAdd->GetWorld();

		const auto AddItems = Cast<AInventoryItem>(ItemToAdd);
		InventoryUpdateDelegate.Broadcast(AddItems, true);
		return true;
	}

	return false;
}

void UInventoryComponent::DeleteItemFromArray(AInventoryBaseItem* ItemToRemove)
{
	Items.RemoveSingle(ItemToRemove);
	ItemToRemove->SetOwningInventory(nullptr);
	ItemToRemove->MyWorld = nullptr;
	FSelectionChangeDel.Broadcast();
	const auto RemoveItems = Cast<AInventoryItem>(ItemToRemove);
	InventoryUpdateDelegate.Broadcast(RemoveItems, false);
}

bool UInventoryComponent::RemoveItem(AInventoryBaseItem* ItemToRemove)
{
	CreateInventorySystemInstance();
	if(ItemToRemove)
	{
		DeleteItemFromArray(ItemToRemove);
		return true;
	}
	return false;
}

bool UInventoryComponent::DropInventoryItem(AInventoryBaseItem* ItemToDrop)
{
	CreateInventorySystemInstance();
	if(ItemToDrop)
	{
		ItemToDrop->DropTheItem();
		DeleteItemFromArray(ItemToDrop);
		return true;
	}

	return false;
}

void UInventoryComponent::Combi_Item(AInventoryItem* ItemToCombi)
{
	if(!DataTable.Contains(FName(*ItemToCombi->GetItemName().ToString()))) return;
	const FItemInfo SearchTheMap = DataTable[FName(*ItemToCombi->GetItemName().ToString())];

	if(SearchTheMap.Item)
		UE_LOG(LogTemp, Warning, TEXT(" 아이템의 이름은 : %s"), *SearchTheMap.Item->GetName());
	
	// 조합할 아이템을 찾고, 해당 개수 이상이면 조합을 실행한다. ex) Clothes x 3 = Bandage
	if(CheckCanCombination(ItemToCombi, SearchTheMap))
	{
		int32 ItemCountToCombine = 0;

		const int32 OriginItemCount = Items.Num();
		int32 i = 0;
		 // 만약 조합을 할 수 있다면, 조합한 아이템을 삭제하고 새로운 아이템을 넣어준다.

		int k = 0;
		while(i < OriginItemCount)
		{
			if(k >= 50)
			{
				break;
			}
			if(ItemCountToCombine == SearchTheMap.Count)
			{
				break;
			}
			
			if(Items[i]->GetClass() == ItemToCombi->GetClass())
			{
				DeleteItemFromArray(Items[i]);
				ItemCountToCombine++;
				i--;
			}
			i++;
			k++;
		}

		if(SearchTheMap.Item->GetName().Contains("BP_Slaves"))
		{
			if(!SlavesCharacter.IsNull())
			{
				if(UClass* BlueprintClass = SlavesCharacter.LoadSynchronous())
				{
					GetWorld()->SpawnActor(BlueprintClass, &OwningPlayer->GetActorTransform());
				}
			}
		}else
		{
			AddItem(SearchTheMap.Item);
		}
	}
}

void UInventoryComponent::UseItem(AInventoryBaseItem* ItemToUse)
{
	if(AInventoryItem* CastingItemToUse = Cast<AInventoryItem>(ItemToUse))
	{
		CastingItemToUse->UseItem(OwningPlayer);
		RemoveItem(CastingItemToUse);
	}
}

bool UInventoryComponent::CheckCanCombination(AInventoryItem* ItemToCombi, const FItemInfo& ItemInfo)
{
	bool CanCombination = false;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemToCombi->GetItemName().ToString());
	
	
	if(DataTable.Contains(FName(*ItemToCombi->GetItemName().ToString())))
	{
		int32 ItemCount = 0;
		for(auto i : Items)
		{
			if(i->GetClass() == ItemToCombi->GetClass())
			{
				ItemCount++;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("지금 있는 아이템 : %d, 필요한 아이템 : %d"), ItemCount,  ItemInfo.Count);

		if(ItemCount >= ItemInfo.Count)
		{
			CanCombination = true;
		}
	}

	return CanCombination;
}

void UInventoryComponent::CreateInventorySystemInstance()
{
	if(InventorySystemHUDInstance != nullptr) return;
	
	if(OwningPlayer == nullptr)
	{
		OwningPlayer = Cast<APlayerCharacter>(GetOwner());
	}
	else if(OwningPlayer)
	{
		InventorySystemHUDInstance = OwningPlayer->GetInventorySystemHUD();
		if(InventorySystemHUDInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("델리게이트에 추가완료"));
			InventoryUpdateDelegate.AddDynamic(InventorySystemHUDInstance, &UHUD_InventorySystem::RefreshItemInventory);
		}
	}
}

void UInventoryComponent::CreateSelectionHUD()
{
	if(ItemSelectionInstanceClassPtr.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("Null★"));
	}
	if(!ItemSelectionInstanceClassPtr.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("Vaild★"));
		if(UClass* ItemSelectionClass = ItemSelectionInstanceClassPtr.LoadSynchronous())
		{
			UE_LOG(LogTemp, Error, TEXT("Created★"));
			ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), ItemSelectionClass);
			if(ItemSelectionInstance)
			{
				UE_LOG(LogTemp, Error, TEXT("Instance ON★"));
				ItemSelectionInstance->SetParentItem(nullptr);
				ItemSelectionInstance->AddToViewport(1);
				ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
				this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Instance Fail★"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Not Created★"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InVaild★"));
	}
	// const FString RelativePath = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C");
	//if(UObject* BluePrintObject = LoadObject<UObject>(nullptr, TEXT("/Game/Blueprint/Item/Weapon/BP_BaseWeapon.BP_BaseWeapon_C")))

	// FStringClassReference ClassRef(TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection"));
	// FStringClassReference ClassRef(TEXT("'WidgetBlueprint/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection'"));

	/*FStringClassReference ClassRef(TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C"));
	TSoftClassPtr<UHUD_ItemSelectionMenu> BlueprintClassRef(ClassRef);

	if(BlueprintClassRef)
	{
		UE_LOG(LogTemp, Error, TEXT(" PathName : %s"), *BlueprintClassRef->GetPathName());
		UE_LOG(LogTemp, Error, TEXT("AssetName : %s"), *BlueprintClassRef.GetAssetName());
		UE_LOG(LogTemp, Error, TEXT("GetName : %s"), *BlueprintClassRef->GetName());
		UE_LOG(LogTemp, Error, TEXT("FullPathName : %s"), *BlueprintClassRef->GetFullName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BlueprintClassRef 존재 안 함 ★"));
	}

	if(auto LoadedClass = BlueprintClassRef.LoadSynchronous())
	{
		ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), LoadedClass);
		ItemSelectionInstance->SetParentItem(nullptr);
		ItemSelectionInstance->AddToViewport(1);
		ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
		this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
	}*/
	// FStringClassReference ClassRef(TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C"));
	/*FSoftObjectPath ClassRef(TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C"));
	UObject* LoadAsset = ClassRef.TryLoad();
	if(LoadAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 완료★"))
		if(UClass* BlueprintClass = Cast<UClass>(LoadAsset))
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 완료★"))
			ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), BlueprintClass);
			if(ItemSelectionInstance)
			{
				ItemSelectionInstance->SetParentItem(nullptr);
				ItemSelectionInstance->AddToViewport(1);
				ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
				this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 실패★"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 실패★"))
	}
	TSoftObjectPtr<UObject> BlueprintClassRef(ClassRef);*/
	/*if(UObject* Asset = BlueprintClassRef.Get())
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 완료★"))
		if(UClass* BlueprintClass = Cast<UClass>(Asset))
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 완료★"))
			ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), BlueprintClass);
			if(ItemSelectionInstance)
			{
				ItemSelectionInstance->SetParentItem(nullptr);
				ItemSelectionInstance->AddToViewport(1);
				ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
				this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 실패★"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 실패★"))
	}*/
	
	/*if(UClass* LoadedClass = BlueprintClassRef.LoadSynchronous())
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 완료★"))
		ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), LoadedClass);
		if(ItemSelectionInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("셀렉션 인스턴스 생성 완료★"))
			ItemSelectionInstance->SetParentItem(nullptr);
			ItemSelectionInstance->AddToViewport(1);
			ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
			this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
		}
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 실패★"))
	}*/
	
	/*FStringClassReference ItemSelectionPath(TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C"));

	// TSoftObjectPtr<UObject> BlueprintClass = TEXT("/Game/MyFolder/MyBlueprintClass.MyBlueprintClass_C");
	// TSoftObjectPtr<UObject> 
	// if(TSoftClassPtr<UObject> BlueprintClass = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C"))
	// if(UClass* BlueprintClass = Cast<UClass>(ItemSelectionPath.TryLoad()))
	if(UClass* BlueprintClass = ItemSelectionPath.TryLoadClass<UUserWidget>())
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 완료★"))
		ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), BlueprintClass);
		if(ItemSelectionInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("셀렉션 인스턴스 생성 완료★"))
			ItemSelectionInstance->SetParentItem(nullptr);
			ItemSelectionInstance->AddToViewport(1);
			ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
			this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 실패★"))
	}*/
	
	/*if(UObject* BlueprintObject = LoadObject<UObject>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprint/HUD/InventorySystem/WBP_InventoryItemSelection.WBP_InventoryItemSelection_C'")))
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 완료★"))
		if(UClass* BluePrintUClass = Cast<UClass>(BlueprintObject))
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 완료★"))
			ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(GetWorld(), BluePrintUClass);
			if(ItemSelectionInstance)
			{
				UE_LOG(LogTemp, Error, TEXT("셀렉션 인스턴스 생성 완료★"))
				ItemSelectionInstance->SetParentItem(nullptr);
				ItemSelectionInstance->AddToViewport(1);
				ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
				this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("셀렉션 인슽너스 생성 실패★"))
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("블루프린트 클래스 생성 실패★"))	
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("블루프린트 오브젝트 생성 실패★"))
	}*/
	
	/*if(const UBlueprint* BlueprintAsset = Cast<UBlueprint>(LoadObject<UBlueprint>(nullptr, *RelativePath)))
	{
		if(UClass* BlueprintClass = BlueprintAsset->GeneratedClass)
		{
			ItemSelectionInstance = CreateWidget<UHUD_ItemSelectionMenu>(OwningPlayer->GetWorld(), BlueprintClass);
			if(ItemSelectionInstance)
			{
				ItemSelectionInstance->SetParentItem(nullptr);
				ItemSelectionInstance->AddToViewport(1);
				ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
				this->FSelectionChangeDel.AddDynamic(this, &UInventoryComponent::CloseSelection);
			}
		}
	}*/
}

void UInventoryComponent::CreateDescriptionHUD()
{
	if(!ItemDescriptionPtr.IsNull())
	{
		if(UClass* BlueprintClass = ItemDescriptionPtr.LoadSynchronous())
		{
			ItemDescription = CreateWidget<UHUD_ItemDescription>(GetOwningPlayer()->GetWorld(), BlueprintClass);
			if(ItemDescription)
			{
				ItemDescription->SetDescription(FText::FromString(TEXT("hello")));
				ItemDescription->AddToViewport(0);
				ItemDescription->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		
	}
	
	/*const FString RelativePath = TEXT("/Game/Blueprint/HUD/InventorySystem/WBP_ItemDescription");

	if(const UBlueprint* BlueprintAsset = Cast<UBlueprint>(LoadObject<UBlueprint>(nullptr, *RelativePath)))
	{
		if(UClass* BlueprintClass = BlueprintAsset->GeneratedClass)
		{
			ItemDescription = CreateWidget<UHUD_ItemDescription>(GetOwningPlayer()->GetWorld(), BlueprintClass);
			if(ItemDescription)
			{
				ItemDescription->SetDescription(FText::FromString(TEXT("hello")));
				ItemDescription->AddToViewport(0);
				ItemDescription->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}*/
}

void UInventoryComponent::CloseSelection()
{
	if(ItemSelectionInstance)
	{
		ItemSelectionInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}