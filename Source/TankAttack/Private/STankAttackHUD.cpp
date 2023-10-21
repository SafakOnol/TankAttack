// Fill out your copyright notice in the Description page of Project Settings.


#include "STankAttackHUD.h"

#include "TankAttackGameMode.h"
#include "Components/TextBlock.h"

void USTankAttackHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void USTankAttackHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	ATankAttackGameMode* GameModeInstance = GetWorld()->GetAuthGameMode<ATankAttackGameMode>();

	if(GameModeInstance)
	{
		CountdownTimer = GameModeInstance->GetRemainingTime();
		CountdownTextBlock->SetText(FText::FromString(FString::FromInt(CountdownTimer)));

		RemainingTowerCount = GameModeInstance->GetTargetTowerCount();
		RemainingTowerTextBlock->SetText(FText::FromString(FString::FromInt(RemainingTowerCount)));
	}
	
}
