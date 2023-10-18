#pragma once

struct EquipmentItemType
{
	
};

UENUM(BlueprintType)
enum class EPartOfArmor : uint8
{
	EPA_Helmet UMETA(DisplayName = "Helmet"),
	EPA_Armor UMETA(DisplayName = "Armor"),
	EPA_Pants UMETA(DisplayName = "Pants")
};