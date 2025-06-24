#include "FChaosGameplayTags.h"

#include "GameplayTagsManager.h"

FChaosGameplayTags FChaosGameplayTags::GameplayTags;

void FChaosGameplayTags::InitializeNativeGameplayTags()
{
	/* Vital Attributes */
	GameplayTags.Message_Player_Attribute_Health_Changed = UGameplayTagsManager::Get().
	AddNativeGameplayTag(FName(TEXT("Message.Player.Attribute.Health.Changed")), TEXT("Attribute Health Changed Message for local player"));

	/* Secondary Attributes */
	GameplayTags.Message_Player_Attribute_MaxHealth_Changed = UGameplayTagsManager::Get().
	AddNativeGameplayTag(FName(TEXT("Message.Player.Attribute.MaxHealth.Changed")), TEXT("Attribute Max Health Changed Message for local player"));
}
