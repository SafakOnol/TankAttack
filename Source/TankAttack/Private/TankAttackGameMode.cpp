// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAttackGameMode.h"

#include "STankAttackPlayerController.h"
#include "STankPawn.h"
#include "STowerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATankAttackGameMode::KillActor(AActor* KilledActor)
{
	if(KilledActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankAttackPlayerController)
		{
			TankAttackPlayerController->SetPlayerEnabledState(false);
		}
		GameWon(false); // lose condition
	}

	else if (ASTowerPawn* KilledTower = Cast<ASTowerPawn>(KilledActor))
	{
		KilledTower->HandleDestruction();
		TargetTowers--;
		EncounterCountdown += 7.f;
		if (TargetTowers == 0) // win condition
		{
			GameWon(true);
		}
	}
}

void ATankAttackGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
}


void ATankAttackGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount(); // set the target tower int32 to current number of towers on map at the beginning.
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
		GetWorldTimerManager().SetTimer(EncounterCountdownTimerHandle, this, &ATankAttackGameMode::ApplyCountdown, 1.f, true, StartDelay);
	}
}

int32 ATankAttackGameMode::GetTargetTowerCount()
{
	TArray<AActor*> TowersOnMap; // declare an array
	UGameplayStatics::GetAllActorsOfClass(this, ASTowerPawn::StaticClass(), TowersOnMap); // set the array to TowerPawn class
	return TowersOnMap.Num(); // return the number
}

void ATankAttackGameMode::ApplyCountdown()
{
	EncounterCountdown--;

	int32 Seconds = ceil(EncounterCountdown);
	int32 SecondsToDisplay = Seconds % 60; // TODO: there should be a better way for this
	int32 Minutes = floor(Seconds/60);
	
	UE_LOG(LogTemp, Display, TEXT("Minutes: %d"), Minutes);
	UE_LOG(LogTemp, Display,  TEXT("Seconds: %d"),SecondsToDisplay);

	if ( Minutes == 0 && Seconds < 0)
	{
		KillActor(Tank);
		UE_LOG(LogTemp, Display, TEXT("Timeout!"));
	}
	
}
