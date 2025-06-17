// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ChaosPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Character/ChaosPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"

void AChaosPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AChaosPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChaosPlayerController::Move);
	}
}

void AChaosPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>().GetSafeNormal();

	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Green, FString::Printf(TEXT("Move Direction: %s"), *MoveDirection.ToString()));
	}

	if (AChaosPlayerCharacter* PlayerCharacter = GetPawn<AChaosPlayerCharacter>())
	{
		PlayerCharacter->AddMovementInput(ForwardDirection, MoveDirection.Y);
		PlayerCharacter->AddMovementInput(RightDirection, MoveDirection.X);
	}
}
