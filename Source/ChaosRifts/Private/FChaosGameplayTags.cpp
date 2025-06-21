#include "FChaosGameplayTags.h"

#include "GameplayTagsManager.h"

FChaosGameplayTags FChaosGameplayTags::GameplayTags;

void FChaosGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Message_Attribute_Changed = UGameplayTagsManager::Get().
	AddNativeGameplayTag(FName(TEXT("Message.Attribute.Changed")), TEXT("Attribute Changed Message"));
}
