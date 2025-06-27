#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct CHAOSRIFTS_API FChaosGameplayTags
{
public:
	/* Gameplay Message Channels */
	FGameplayTag Message_Player_Attribute_Health_Changed;
	FGameplayTag Message_Player_Attribute_MaxHealth_Changed;

	/* Input Tags */
	FGameplayTag Input_LeftMouse;

public:
	static void InitializeNativeGameplayTags();
	static const FChaosGameplayTags& Get() { return GameplayTags; }

private:
	static FChaosGameplayTags GameplayTags;
};
