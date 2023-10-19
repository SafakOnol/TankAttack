// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameUnitPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SProjectile.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ASGameUnitPawn::ASGameUnitPawn()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ASGameUnitPawn::HandleDestruction()
{
	// TODO: Visual/Sound Effects
	if(DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	
}

void ASGameUnitPawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); // this is a world rotation
	FRotator LookAtRotation(0.f, ToTarget.Rotation().Yaw, 0.f); // Currently I only want to get Yaw value, so we're setting pitch and roll to 0.

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(),
		LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f));
}

void ASGameUnitPawn::Fire()
{
	// Draw Debug sphere
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPointLocation, 25.f, 12, FColor::Red, false, 3.f);
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<ASProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileRotation);
	Projectile->SetOwner(this); // store the projectile's owner to the actor that spawned it.
}

