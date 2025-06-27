// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ChaosInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FChaosInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UInputAction> InputAction;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
};

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UChaosInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	const TArray<FChaosInputAction>& GetAbilityInputActions() const { return AbilityInputActions; }

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogTagNotFound = false) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FChaosInputAction> AbilityInputActions;
};
