// Fill out your copyright notice in the Description page of Project Settings.


#include "STankPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	Super::BeginPlay();

	PlayerControllerReference = Cast<APlayerController>(GetController());
	// Get Controller is actually a type APlayerController pointer stored in AController pointer,
	// therefore we can Cast it back to APlayerController, which is our type of pointer (pointers have to reference to same types)
}

// Called to bind functionality to input
void ASTankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTankPawn::Move);

	PlayerInputComponent->BindAxis("Turn", this, &ASTankPawn::Turn);
	
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

void ASTankPawn::RotateTurretX(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurretTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

