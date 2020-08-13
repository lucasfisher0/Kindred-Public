#include "Items/RPGItem.h"

FName URPGItem::GetEquipType() const
{
    return ItemType.GetName();
}

EEquipmentSlots URPGItem::K2_GetEquipmentSlot()
{
    return GetEquipSlot();
}

EEquipmentSlots URPGItem::GetEquipSlot()
{
    return EEquipmentSlots::ET_None;
}

bool URPGItem::K2_GetEquipmentInfo(FEquipmentItem& Out)
{
    return GetEquipInfo(Out);
}

bool URPGItem::GetEquipInfo(FEquipmentItem& Out)
{
    return false;
}

bool URPGItem::IsConsumable() const
{
    if (MaxCount <= 0)
    {
        return true;
    }
    return false;
}

FString URPGItem::GetIdentifierString() const
{
    return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId URPGItem::GetPrimaryAssetId() const
{
    // This is a DataAsset and not a blueprint so we can just use the raw FName
    // For blueprints you need to handle stripping the _C suffix
    return FPrimaryAssetId(ItemType, GetFName());
}