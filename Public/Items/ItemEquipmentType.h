// Coded by Lucas Fisher 2019-2020

#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "ItemEquipmentType.generated.h"

/**
 * 
 */
UCLASS()
class KSPROTOTYPE_API UItemEquipmentType : public URPGItem
{
	GENERATED_BODY()

public:
	UItemEquipmentType()
	{
		ItemType = URPGAssetManager::EquipmentItemType;
	}

	// Equip Slot Override
	virtual EEquipmentSlots GetEquipSlot() override;

	// Equipment Info Override -- Contains Damages, Armor, etc.
	virtual bool GetEquipInfo(FEquipmentItem& Out) override;

	// Information Needed for all Armor or Weapons
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FEquipmentItem EquipmentInfo;
};
