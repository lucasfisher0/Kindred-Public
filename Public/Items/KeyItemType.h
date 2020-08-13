// Coded by Lucas Fisher 2019-2020

#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "KeyItemType.generated.h"

/**
 * 
 */
UCLASS()
class KSPROTOTYPE_API UKeyItemType : public URPGItem
{
	GENERATED_BODY()

	UKeyItemType()
	{
		ItemType = URPGAssetManager::KeyItemType;
	}
};
