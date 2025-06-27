// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "ChaosPlayerController.generated.h"

class UChaosAbilitySystemComponent;
struct FGameplayTag;
class UChaosInputConfig;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API AChaosPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UChaosInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UChaosAbilitySystemComponent> ChaosAbilitySystemComponent;

private:
	void Move(const FInputActionValue& Value);

	void AbilityInputTagPressed(const FGameplayTag InputTag);
	void AbilityInputTagReleased(const FGameplayTag InputTag);
	void AbilityInputTagHeld(const FGameplayTag InputTag);

	UChaosAbilitySystemComponent* GetChaosAbilitySystemComponent();
};
