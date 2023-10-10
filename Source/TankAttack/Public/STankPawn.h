// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameUnitPawn.h"
#include "STankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TANKATTACK_API ASTankPawn : public ASGameUnitPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTankPawn();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;
	
};
