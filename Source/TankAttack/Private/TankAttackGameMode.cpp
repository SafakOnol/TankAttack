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

	HandleGameStart();
	
}

void ATankAttackGameMode::HandleGameStart()
{
	Tank = Cast<ASTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankAttackPlayerController = Cast<ASTankAttackPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if(TankAttackPlayerController)
	{
		TankAttackPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate PlayerEnableTimerDelegate =  FTimerDelegate::CreateUObject(TankAttackPlayerController,
													&ASTankAttackPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
		
		
	}
}
