// Fill out your copyright notice in the Description page of Project Settings.


#include "STowerPawn.h"
#include "STankPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ASTowerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsTankInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
	
}

void ASTowerPawn::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ASTowerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Call Tank pointer from Tank class
	Tank = Cast<ASTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ASTowerPawn::CheckFireCondition, FireRate, true);
}

void ASTowerPawn::CheckFireCondition()
{
	if(Tank == nullptr)
	{
		return;
	}
	
	if(IsTankInRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ASTowerPawn::IsTankInRange()
{
	if(Tank && !Tank->IsHidden())
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance < FireRange)
		{
			return true;
		}
	}
	return false;
}

