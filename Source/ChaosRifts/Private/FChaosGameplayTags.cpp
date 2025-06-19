#include "FChaosGameplayTags.h"

#include "GameplayTagsManager.h"

FChaosGameplayTags FChaosGameplayTags::GameplayTags;

void FChaosGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Message_AttributeChanged = UGameplayTagsManager::Get().
	AddNativeGameplayTag(FName(TEXT("Message.AttributeChanged")), TEXT("Attribute Changed Message"));
}
