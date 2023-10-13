// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAttackGameMode.h"

#include "STankAttackPlayerController.h"
#include "STankPawn.h"
#include "STowerPawn.h"
#include "Kismet/GameplayStatics.h"

void ATankAttackGameMode::KillActor(AActor* KilledActor)
{
	if(KilledActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankAttackPlayerController)
		{
			TankAttackPlayerController->SetPlayerEnabledState(false);
		}
		
	}

	else if (ASTowerPawn* KilledTower = Cast<ASTowerPawn>(KilledActor))
	{
		KilledTower->HandleDestruction();
	}
}

void ATankAttackGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ASTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankAttackPlayerController = Cast<ASTankAttackPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	
}
