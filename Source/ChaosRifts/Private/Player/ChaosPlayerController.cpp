// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ChaosPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ChaosAbilitySystemComponent.h"
#include "Input/ChaosInputComponent.h"

void AChaosPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
}

void AChaosPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UChaosInputComponent* ChaosInputComponent = Cast<UChaosInputComponent>(InputComponent);
	
	ChaosInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChaosPlayerController::Move);

	ChaosInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputTagPressed, 
		&ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AChaosPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>().GetSafeNormal();

	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MoveDirection.Y);
		ControlledPawn->AddMovementInput(RightDirection, MoveDirection.X);
	}
}

void AChaosPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	
}

void AChaosPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (GetChaosAbilitySystemComponent())
	{
		GetChaosAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	}
}

void AChaosPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (GetChaosAbilitySystemComponent())
	{
		GetChaosAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
	}
}

UChaosAbilitySystemComponent* AChaosPlayerController::GetChaosAbilitySystemComponent()
{
	if (ChaosAbilitySystemComponent == nullptr)
	{
		ChaosAbilitySystemComponent = Cast<UChaosAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return ChaosAbilitySystemComponent;
}
