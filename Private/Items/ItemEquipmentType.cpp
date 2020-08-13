// Coded by Lucas Fisher 2019-2020


#include "Items/ItemEquipmentType.h"

EEquipmentSlots UItemEquipmentType::GetEquipSlot()
{
    return EquipmentInfo.EquipmentSlot;
}

bool UItemEquipmentType::GetEquipInfo(FEquipmentItem& Out)
{
    Out = EquipmentInfo;
    return true;
}
