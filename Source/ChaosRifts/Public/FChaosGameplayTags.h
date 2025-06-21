#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct CHAOSRIFTS_API FChaosGameplayTags
{
public:
	// Gameplay Message Channels
	FGameplayTag Message_Attribute_Changed;

public:
	static void InitializeNativeGameplayTags();
	static const FChaosGameplayTags& Get() { return GameplayTags; }

private:
	static FChaosGameplayTags GameplayTags;
};
