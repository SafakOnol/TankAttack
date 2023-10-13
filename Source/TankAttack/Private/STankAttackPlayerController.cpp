// Fill out your copyright notice in the Description page of Project Settings.


#include "STankAttackPlayerController.h"

void ASTankAttackPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}
