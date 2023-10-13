// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STankAttackPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKATTACK_API ASTankAttackPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
};
