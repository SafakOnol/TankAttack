// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankAttackGameMode.generated.h"

class ASTankAttackPlayerController;
class ASTankPawn;
/**
 * 
 */
UCLASS()
class TANKATTACK_API ATankAttackGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void KillActor(AActor* KilledActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame(); // Function implementation is in BP, don't need a body on cpp 

	UFUNCTION(BlueprintImplementableEvent)
	void GameWon(bool bWonGame);


	// COUNTDOWN TIMER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (AllowPrivateAccess = "true"))
	FTimerHandle EncounterCountdownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (AllowPrivateAccess = "true"))
	float EncounterCountdown = 20.f;
	
	UFUNCTION()
	void ApplyCountdown(); 
	
private:

	ASTankPawn* Tank;
	ASTankAttackPlayerController* TankAttackPlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Mode", meta = (AllowPrivateAccess = "true"))
	float StartDelay = 4.f;
	
	void HandleGameStart();

	UPROPERTY()
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	
};
