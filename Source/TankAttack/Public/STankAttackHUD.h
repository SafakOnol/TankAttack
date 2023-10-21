// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STankAttackHUD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKATTACK_API USTankAttackHUD : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountdownTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RemainingTowerTextBlock;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	int32 CountdownTimer;

	int32 RemainingTowerCount;
	
	
};
