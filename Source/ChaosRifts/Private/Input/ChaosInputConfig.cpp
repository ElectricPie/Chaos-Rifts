// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ChaosInputConfig.h"

const UInputAction* UChaosInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogTagNotFound) const
{
	for (const auto& Aciton : AbilityInputActions)
	{
		if (Aciton.InputAction && Aciton.InputTag.MatchesTagExact(InputTag))
		{
			return Aciton.InputAction;
		}
	}

	if (bLogTagNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("No input action found for tag [%s] in Input Config [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
