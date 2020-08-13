#pragma once

#include "KSPrototype.h"
#include "RPGTypes.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "RPGAssetManager.h"
#include "RPGItem.generated.h"

class UKSGameplayAbility;

UCLASS(Abstract, BlueprintType)
class KSPROTOTYPE_API URPGItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    URPGItem()
        : Value(0),
        Quantity(1),
        MaxCount(1)
    {
        UE_LOG(LogInv, Log, TEXT("Item: %s constructed."), *ItemName.ToString());
    }
    
    /** Type of this item, set in native parent class */
    UPROPERTY(BlueprintReadOnly, Category = Item)
    FPrimaryAssetType ItemType;

    /** User-visible short name */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemName;
    UFUNCTION(BlueprintGetter, Category = Item)
    FText GetItemName() const { return ItemName; }

    /** User-visible long description */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemDescription;
    UFUNCTION(BlueprintGetter, Category = Item)
    FText GetItemDescription() const { return ItemDescription; }
    
    /** Icon to display */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FSlateBrush ItemIcon;

    /** Soul sell price */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 Quantity;

    UFUNCTION(BlueprintPure, Category = Item)
    FName GetEquipType() const;

    /* Blueprint Get Equipment Slot */
    UFUNCTION(BlueprintPure, meta=(DisplayName = "Get Equipment Slot"),Category = Item)
    EEquipmentSlots K2_GetEquipmentSlot();
    virtual EEquipmentSlots GetEquipSlot();

    /* Blueprint Get Equipment Info */
    UFUNCTION(BlueprintPure, meta=(DisplayName = "Get Equipment Info"),Category = Item)
    bool K2_GetEquipmentInfo(FEquipmentItem& Out);
    virtual bool GetEquipInfo(FEquipmentItem& Out);
    
    /** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 MaxCount;

    /** Returns if the item is consumable (MaxCount <= 0)*/
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
    bool IsConsumable() const;

    /** Ability to grant if this item is slotted */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    TSubclassOf<UKSGameplayAbility> GrantedAbility;

    /** Returns the logical name, equivalent to the primary asset id */
    UFUNCTION(BlueprintCallable, Category = Item)
    FString GetIdentifierString() const;

    /** Overridden to use saved type */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};