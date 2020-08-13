// Coded by Lucas Fisher 2019-2020

#pragma once

#include "CoreMinimal.h"
#include "RPGItem.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "ItemWorldActor.generated.h"

UCLASS()
class KSPROTOTYPE_API AItemWorldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemWorldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* RootDummy;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSoftObjectPath ItemPath;
	
	UPROPERTY()
	URPGItem* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 ItemQuantity = 1;
	
	UPROPERTY()
	UTextRenderComponent* EditorHint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
