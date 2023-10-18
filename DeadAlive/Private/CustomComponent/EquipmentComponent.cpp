#include "CustomComponent/EquipmentComponent.h"

#include "Items/ArmorItems.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEquipmentComponent::SetArmorItems(EPartOfArmor ArmorName, AArmorItems* Item)
{
	switch (ArmorName)
	{
	case EPartOfArmor::EPA_Helmet :
		Helmet = Item;
		ItemsArray[0] = true;
		ArmorContainer.Add(Helmet);
		break;
	case EPartOfArmor::EPA_Armor :
		Armor = Item;
		ItemsArray[1] = true;
		ArmorContainer.Add(Armor);
		break;
	case EPartOfArmor::EPA_Pants :
		Pants = Item;
		ItemsArray[2] = true;
		ArmorContainer.Add(Pants);
		break;
	}
}

void UEquipmentComponent::DeleteArmorItems(EPartOfArmor ArmorName)
{
	switch (ArmorName)
	{
	case EPartOfArmor::EPA_Helmet :
		ItemsArray[0] = false;
		ArmorContainer.Remove(Helmet);
		Helmet = nullptr;
		break;
	case EPartOfArmor::EPA_Armor :
		ItemsArray[1] = false;
		ArmorContainer.Remove(Armor);
		Armor = nullptr;
		break;
	case EPartOfArmor::EPA_Pants :
		ItemsArray[2] = false;
		ArmorContainer.Remove(Pants);
		Pants = nullptr;
		break;
	}
}

void UEquipmentComponent::DamageDistribution(const float TakenDamage)
{
	const int TotalArmorCount = ArmorContainer.Num();
	const float DistributedDamage = TakenDamage / TotalArmorCount;

	for(const auto i : ArmorContainer)
	{
		if(i)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *i->GetName());
			i->GetHit(FVector::ZeroVector, nullptr, DistributedDamage);
		}
		if(TotalArmorCount != ArmorContainer.Num())
			break;
	}
	
}

bool UEquipmentComponent::CanAcceptAttack()
{
	if(ArmorContainer.Num() > 0)
		return true;
	return false;
}

