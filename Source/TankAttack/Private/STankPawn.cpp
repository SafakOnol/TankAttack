// Fill out your copyright notice in the Description page of Project Settings.


#include "STankPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASTankPawn::ASTankPawn()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASTankPawn::BeginPlay()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Super::BeginPlay();

	PlayerControllerReference = Cast<APlayerController>(GetController());
	// Get Controller is actually a type APlayerController pointer stored in AController pointer,
	// therefore we can Cast it back to APlayerController, which is our type of pointer (pointers have to reference to same types)
}

void ASTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Using APlayerController::GetHitResultUnderCursor to line trace to mouse cursor and getting hit information
	if(PlayerControllerReference)
	{
		// We're passing the FHitResult as reference but not const, because we need to change the information on HitResult with every hit.
		FHitResult HitResult;
		PlayerControllerReference->GetHitResultUnderCursor(ECC_Visibility,false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.f, 12, FColor::Red, false, -1.f);
		RotateTurret(HitResult.ImpactPoint);
	}
}

// Called to bind functionality to input
void ASTankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTankPawn::Move);

	PlayerInputComponent->BindAxis("Turn", this, &ASTankPawn::Turn);

	//PlayerInputComponent->BindAxis("RotateTurret", this, ASGameUnitPawn::RotateTurret);
	
}

// TANK MOVEMENT
void ASTankPawn::Move(float Value)
{
	FVector DeltaLocation(0.f); // FVector::ZeroVector
	// X = Value * DeltaTime * Speed
	// Get DeltaTime by this: "UGameplayStatics::GetWorldDeltaSeconds(this)"
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ASTankPawn::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	// Yaw = Value * DeltaTime * TurnRate
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}




