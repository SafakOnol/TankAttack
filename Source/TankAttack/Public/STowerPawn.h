// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameUnitPawn.h"
#include "STowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TANKATTACK_API ASTowerPawn : public ASGameUnitPawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;

private:

	class ASTankPawn* Tank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireRange = 700.f;

	
	
};
