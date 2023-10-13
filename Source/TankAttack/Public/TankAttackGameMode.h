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

private:

	ASTankPawn* Tank;
	ASTankAttackPlayerController* TankAttackPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();
};
