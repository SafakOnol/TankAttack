// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAttackGameMode.h"

#include "STankAttackPlayerController.h"
#include "STankPawn.h"
#include "STowerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATankAttackGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankAttackGameMode::KillActor(AActor* KilledActor)
{
	if(KilledActor == Tank && Tank->bAlive)
	{
		Tank->HandleDestruction();
		if (TankAttackPlayerController)
		{
			TankAttackPlayerController->SetPlayerEnabledState(false);
		}
		GameWon(false); // lose condition
		Tank->bAlive = false;
	}

	else if (ASTowerPawn* KilledTower = Cast<ASTowerPawn>(KilledActor))
	{
		KilledTower->HandleDestruction();
		TargetTowers--;
		EncounterCountdown += 7.f;
		UE_LOG(LogTemp, Display, TEXT("Tower Destroyed!"));
		if (TargetTowers == 0) // win condition
		{
			GameWon(true);
		}
	}
}

void ATankAttackGameMode::HandleTargetDestroyed()
{
	KillActor(this);
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

int32 ATankAttackGameMode::GetRemainingTime()
{
	return SecondsToDisplay;
}

void ATankAttackGameMode::ApplyCountdown()
{
	if(TargetTowers == 0)
	{
		return;
	}
	Seconds = ceil(EncounterCountdown);
	SecondsToDisplay = Seconds % 60; // TODO: there should be a better way for this
	Minutes = floor(Seconds/60);
	
	EncounterCountdown--;
	
	//UE_LOG(LogTemp, Display, TEXT("Minutes: %d"), Minutes);
	//UE_LOG(LogTemp, Display,  TEXT("Seconds: %d"),SecondsToDisplay);

	if ( Minutes < 1 && Seconds < 1)
	{
		UE_LOG(LogTemp, Display, TEXT("Timeout!"));
		EncounterCountdown = 0;
		KillActor(Tank);
		
	}
	
}
