// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ChaosGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UChaosGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FGameplayTag GetStartupGameplayTag() const { return StartupGameplayTag; }

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupGameplayTag = FGameplayTag::EmptyTag;
};
