// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameUnitPawn.h"
#include "STowerPawn.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetDestroyed);
UCLASS()
class TANKATTACK_API ASTowerPawn : public ASGameUnitPawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();

protected:

	virtual void BeginPlay() override;

private:

	class ASTankPawn* Tank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
	bool IsTankInRange();
	
};
