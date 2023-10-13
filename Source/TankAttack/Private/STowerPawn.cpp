// Fill out your copyright notice in the Description page of Project Settings.


#include "STowerPawn.h"
#include "STankPawn.h"
#include "Kismet/GameplayStatics.h"

void ASTowerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance < FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
		
	}
	
}

void ASTowerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Call Tank pointer from Tank class
	Tank = Cast<ASTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}
