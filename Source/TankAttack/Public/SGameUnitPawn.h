// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SGameUnitPawn.generated.h"

class UCapsuleComponent;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;
UCLASS()
class TANKATTACK_API ASGameUnitPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASGameUnitPawn();

	void HandleDestruction(); // virtual???

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh; // no need for forward declaration since staticmeshcomponents are already included in actor

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat");
	TSubclassOf<class ASProjectile> ProjectileClass; // This allows us to access another class

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* PawnDeathSound;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ShakeScale = 1.f;
};
