// Coded by Lucas Fisher 2019-2020


#include "Items/ItemWorldActor.h"
#include "Items/ItemActiveType.h"
#include "Items/ItemEquipmentType.h"
#include "Items/KeyItemType.h"

// Sets default values
AItemWorldActor::AItemWorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootDummy = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootDummy);
	
	// Box Collider
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	BoxCollision->SetBoxExtent(FVector(30.f, 30.f, 30.f), true);
	BoxCollision->SetupAttachment(RootDummy);
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 30.f));

	EditorHint = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("EditorTextHint"));
	EditorHint->SetupAttachment(RootDummy);
	EditorHint->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	EditorHint->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	EditorHint->SetHiddenInGame(false);

	
	UObject* MyItem = ItemPath.TryLoad();
	if (MyItem)
	{
		URPGItem* ItemCast = Cast<URPGItem>(MyItem);
		if (ItemCast)
		{
			if (ItemCast->ItemType == URPGAssetManager::KeyItemType)
				ItemCast = Cast<UKeyItemType>(MyItem);
			if (ItemCast->ItemType == URPGAssetManager::ActiveItemType)
				ItemCast = Cast<UItemActiveType>(MyItem);
			if (ItemCast->ItemType == URPGAssetManager::EquipmentItemType)
				ItemCast = Cast<UItemEquipmentType>(MyItem);
		}

		if (ItemCast)
			ItemData = ItemCast;
	}

	if (ItemData)
	{
		// Set Quantity
		ItemData->Quantity = FMath::Max(1, FMath::Min(ItemData->MaxCount, ItemQuantity));

		// Editor Hint Text
		FString HintString = ItemData->ItemName.ToString();
		HintString.Append(" x"); HintString.AppendInt(ItemData->Quantity);
		
		EditorHint->SetText(FText::FromString(HintString));
	}
	else
	{
		EditorHint->SetText(TEXT("UNDEFINED"));
		UE_LOG(LogInv, Warning, TEXT("ItemWorldActor does not have a valid ItemData!"));
	}
}

// Called when the game starts or when spawned
void AItemWorldActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemWorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

