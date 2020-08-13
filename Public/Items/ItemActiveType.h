// Coded by Lucas Fisher 2019-2020

#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "ItemActiveType.generated.h"

/**
 * 
 */
UCLASS()
class KSPROTOTYPE_API UItemActiveType : public URPGItem
{
	GENERATED_BODY()
	
public:
	UItemActiveType()
	{
		ItemType = URPGAssetManager::ActiveItemType;
	}
};
