// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"

#include "STankAttackPlayerController.h"
#include "STankPawn.h"
#include "TankAttackGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectBaseUtility.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::DamageTaken); // This is called when OnTakeAnyDamage is broadcasted

	TankAttackGameMode = Cast<ATankAttackGameMode>(UGameplayStatics::GetGameMode(this));
	
}


void USHealthComponent::DamageTaken(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (DamageAmount < 0.f) return;

	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (Health < 0.1f && TankAttackGameMode)
	{
		TankAttackGameMode->KillActor(DamagedActor);
	}
	
}

// Called every frame
void USHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

