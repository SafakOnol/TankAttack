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

private:

	ASTankPawn* Tank;
	ASTankAttackPlayerController* TankAttackPlayerController;
};
