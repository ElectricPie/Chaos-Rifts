// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ChaosPlayerState.h"

#include "AbilitySystemComponent.h"
#include "FChaosGameplayTags.h"
#include "AbilitySystem/ChaosAttributeSet.h"
#include "GameFramework/GameplayMessageSubsystem.h"

AChaosPlayerState::AChaosPlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UChaosAttributeSet>(TEXT("AttributeSet"));


	if (const UChaosAttributeSet* ChaosAttributeSet = Cast<UChaosAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);

				FAttributeChangedMessage AttributeChangedMessage;
				AttributeChangedMessage.AttributeName = FText::FromString("Health");
				AttributeChangedMessage.AttributeValue = Data.NewValue;

				MessageSubsystem.BroadcastMessage(FChaosGameplayTags::Get().Message_Attribute_Changed, AttributeChangedMessage);
			}
		);
	}
}
