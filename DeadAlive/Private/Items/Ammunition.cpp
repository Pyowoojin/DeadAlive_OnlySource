#include "Items/Ammunition.h"
#include "Attributes/CharacterAttribute.h"
#include "HUD/WeaponInfoWidget.h"
#include "Attributes/WeaponAttributes.h"
#include "PlayerCharacter.h"

AAmmunition::AAmmunition()
{
	SkeletalComponent->SetSimulatePhysics(true);
	ItemAttributes = CreateDefaultSubobject<UWeaponAttributes>("ItemAttributes");
}

void AAmmunition::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// 위젯에 아이템 이름 설정
void AAmmunition::SetItemNameForWidget() const
{
	if(WeaponInfo && ItemAttributes)
	{
		WeaponInfo->SetItemName(ItemAttributes->GetItemName());
		WeaponInfo->SetAmmo(ItemAttributes->GetAmmoCount());
	}
}

// 총알이라면 Ammo 개수를 늘려줌
void AAmmunition::IPickUpItem(ABaseItem* Item, APlayerCharacter* Player)
{
	Super::IPickUpItem(Item, Player);
	Player->GetCharAttribute()->SetAmmoCountForAmmoType(ItemAttributes->GetWeaponType(), ItemAttributes->GetAmmoCount());
	Destroy();
}

void AAmmunition::BeginPlay()
{
	Super::BeginPlay();
	SetItemNameForWidget();
}
