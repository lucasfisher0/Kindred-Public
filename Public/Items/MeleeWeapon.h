// Coded by Lucas Fisher 2019-2020

#pragma once

#include "CoreMinimal.h"
#include "RPGTypes.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Containers/Array.h"
#include "NiagaraFunctionLibrary.h" 
#include "MeleeWeapon.generated.h"

UCLASS(BlueprintType)
class AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

	//
	//	WEAPON DAMAGE
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDamageTyped> WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAfflictionStatus> WeaponAffliction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TracesPerSwing;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	//
	//	WEAPON TRACE
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = "Components")
	USceneComponent* WeaponRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = "Components")
	UBoxComponent* TopTrace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = "Components")
	UBoxComponent* BottomTrace;
	
	bool bIsAttacking;
	float TraceBoxOffset;

	TArray<UBoxComponent*> TraceBoxes;
	TArray<FVector> TraceStartLocations;
	FTransform CalculateTraceBoxSpawnOffset(int loopIndex) const;

	TArray<AActor*> AlreadyHitActors;
	TArray<AActor*> HitActors;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attack Functions
	UFUNCTION(BlueprintCallable)
	virtual void StartAttack();
	UFUNCTION(BlueprintCallable)
	virtual void StopAttack(bool ResetCombo);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Debug")
	void DrawTraceDebug(FVector Start, FVector End);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* BloodParticleSystem;
};
