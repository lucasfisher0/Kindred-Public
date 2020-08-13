// Coded by Lucas Fisher 2019-2020


#include "Items/MeleeWeapon.h"
#include "Enemy/RPG_EnemyBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "KSPrototype.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, Log, All);

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickInterval = 0.1f; // Maybe allow to tick every frame?

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
	SetRootComponent(WeaponMesh);
	
	WeaponRoot = CreateDefaultSubobject<USceneComponent>("WeaponRootComponent");
	if (WeaponRoot)
	{
		WeaponRoot->SetupAttachment(WeaponMesh);
	}
	
	TopTrace = CreateDefaultSubobject<UBoxComponent>("TopTraceComponent");
	if (TopTrace)
	{
		TopTrace->SetupAttachment(WeaponMesh);
		TopTrace->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	BottomTrace = CreateDefaultSubobject<UBoxComponent>("BottomTraceComponent");
	if (BottomTrace)
	{
		BottomTrace->SetupAttachment(WeaponMesh);
		BottomTrace->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bIsAttacking = false;
}

FTransform AMeleeWeapon::CalculateTraceBoxSpawnOffset(int loopIndex) const
{
	FVector newLocation;
	newLocation = BottomTrace->GetRelativeLocation();
	newLocation.Z += (loopIndex*TraceBoxOffset);
	
	return FTransform(BottomTrace->GetRelativeRotation().Quaternion(), newLocation, BottomTrace->GetRelativeScale3D());
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	FVector tmpVector = (TopTrace->GetRelativeLocation())-(BottomTrace->GetRelativeLocation());
	TraceBoxOffset = (tmpVector / FVector(1.0, 1.0, float(TracesPerSwing+1))).Z;
	
	UE_LOG(LogWeapon, Log, TEXT("Creating %d extra traces."), TracesPerSwing);
	TraceBoxes.Add(TopTrace);

	for (int i = 1; i < TracesPerSwing; i++)
	{
		FString newName = "Trace";
		newName.AppendInt(i);

		UBoxComponent* NewTrace = NewObject<UBoxComponent>(this);
		NewTrace->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
		NewTrace->SetRelativeTransform(CalculateTraceBoxSpawnOffset(i));
		NewTrace->SetHiddenInGame(true);
		
		TraceBoxes.Add(NewTrace);
	}

	TraceBoxes.Add(BottomTrace);

	for (int i = 0; i < TraceBoxes.Num(); i++)
	{
		TraceStartLocations.Add(TraceBoxes[i]->GetComponentLocation());
	}
}

void AMeleeWeapon::StartAttack()
{
	for (int i = 0; i < TraceBoxes.Num(); i++)
	{
		TraceStartLocations[i] = TraceBoxes[i]->GetComponentLocation();
	}

	bIsAttacking = true; // Actives swing loop of tick
}

void AMeleeWeapon::StopAttack(bool ResetCombo = false)
{
	// If resetting combo, just clear hit actors to allow for them to get hit again
	if (!ResetCombo)
		bIsAttacking = false;
	
	AlreadyHitActors.Empty();
	HitActors.Empty();
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttacking)
	{
		for (int i = 0; i < TraceBoxes.Num(); i++)
		{
			TArray<FHitResult> TraceHits;

			DrawTraceDebug(TraceBoxes[i]->GetComponentLocation(),
			                                    TraceStartLocations[i]);
			if (GetWorld()->LineTraceMultiByChannel(TraceHits, TraceBoxes[i]->GetComponentLocation(),
			                                    TraceStartLocations[i], ECollisionChannel::ECC_GameTraceChannel1))
			{
				//UE_LOG(LogCombat, Log, TEXT("Weapon trace generated %d hits!"), TraceHits.Num());
				for (int j = 0; j < TraceHits.Num(); j++)
				{
					FHitResult LastHit;
					LastHit = TraceHits[j];
					
					if (LastHit.Actor == GetOwner()) // Can't hit Player using the weapon
						continue;

					if (AlreadyHitActors.Contains(LastHit.Actor)) // Can't hit an actor twice
						continue;

					/* COMBAT INTERFACE IS DEAD ;(
					ICombatInterface* AttackerCast = Cast<ICombatInterface>(LastHit.Actor);
					if (AttackerCast)
					{
						
						// Play Particle
						if (BloodParticleSystem)
						{
							UNiagaraComponent* BloodComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BloodParticleSystem, LastHit.Location);
							
							ARPG_EnemyBase* EnemyCast = Cast<ARPG_EnemyBase>(LastHit.Actor);
							if (EnemyCast )
								BloodComponent->AttachToComponent(EnemyCast->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
						}
						
						AttackerCast->Combat_DoDamage(GetOwner(), WeaponDamage, WeaponAffliction);
						UE_LOG(LogCombat, Log, TEXT("Sent damage to actor!"));
						
						AlreadyHitActors.AddUnique(LastHit.GetActor()); // Add actor to already hit list
						
					}
					*/
				} 
			}
			TraceStartLocations[i] = TraceBoxes[i]->GetComponentLocation();
		}
	}
}

void AMeleeWeapon::DrawTraceDebug_Implementation(FVector Start, FVector End)
{
	return;
}
