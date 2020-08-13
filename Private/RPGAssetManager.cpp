// Coded by Lucas Fisher 2019-2020


#include "RPGAssetManager.h"
#include "Items/RPGItem.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType	URPGAssetManager::SkillType = TEXT("Skill");
const FPrimaryAssetType	URPGAssetManager::EquipmentItemType = TEXT("Weapon/Armor Item");
const FPrimaryAssetType	URPGAssetManager::ActiveItemType = TEXT("Equippable Item");
const FPrimaryAssetType	URPGAssetManager::KeyItemType = TEXT("Unusable Item");


URPGAssetManager& URPGAssetManager::Get()
{
    URPGAssetManager* This = Cast<URPGAssetManager>(GEngine->AssetManager);

    if (This)
    {
        return *This;
    }
    else
    {
        UE_LOG(LogKindred, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
        return *NewObject<URPGAssetManager>(); // never calls this
    }

}

void URPGAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    UAbilitySystemGlobals::Get().InitGlobalData();
}


URPGItem* URPGAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{	
    FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

    // This does a synchronous load and may hitch
    URPGItem* LoadedItem = Cast<URPGItem>(ItemPath.TryLoad());

    if (bLogWarning && LoadedItem == nullptr)
    {
        UE_LOG(LogKindred, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
    }

    return LoadedItem;
}
