// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectile.h"

#include "STankPawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ASProjectile::ASProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->MaxSpeed = ProjectileMaxSpeed;
	ProjectileMovementComponent->InitialSpeed = ProjectileInitialSpeed;

	TrailParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Trail Particle System Component");
	TrailParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ASProjectile::OnHit);
	if(LaunchProjectileSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchProjectileSound, GetActorLocation());
	}

	PlayerTank = Cast<ASTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ASProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *HitComponent->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s"), *OtherActor->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Other Component: %s"), *OtherComponent->GetName());
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy(); // in order to avoid a memory issue with particle system we destroy the object before it can spawn a particle
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, MyOwnerInstigator, this, DamageTypeClass); // This boradcasts to OnDamageTaken
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); // spawn projectile
		}
		if(ProjectileHitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ProjectileHitSound,GetActorLocation());
		}

		if(OtherActor == PlayerTank && HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass, ProjectileShakeScale);
		}
		
		//FString DamagedActor = OtherActor->GetName();
		//UE_LOG(LogTemp, Display, TEXT("Damaged: %s"), *FString(DamagedActor));
		
	}
	Destroy();
}

// Called every frame
void ASProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

