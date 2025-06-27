// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ChaosPlayerState.h"

#include "AbilitySystemComponent.h"
#include "FChaosGameplayTags.h"
#include "AbilitySystem/ChaosAbilitySystemComponent.h"
#include "AbilitySystem/ChaosAttributeSet.h"
#include "GameFramework/GameplayMessageSubsystem.h"

AChaosPlayerState::AChaosPlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UChaosAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UChaosAttributeSet>(TEXT("AttributeSet"));
}

void AChaosPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (const UChaosAttributeSet* ChaosAttributeSet = Cast<UChaosAttributeSet>(AttributeSet))
	{
		SetupAttributeChangeDelegate(FChaosGameplayTags::Get().Message_Player_Attribute_Health_Changed, ChaosAttributeSet->GetHealthAttribute(), ChaosAttributeSet);
		SetupAttributeChangeDelegate(FChaosGameplayTags::Get().Message_Player_Attribute_MaxHealth_Changed, ChaosAttributeSet->GetMaxHealthAttribute(), ChaosAttributeSet);
	}
}

void AChaosPlayerState::SetupAttributeChangeDelegate(const FGameplayTag& Tag, const FGameplayAttribute& Attribute, const UChaosAttributeSet* ChaosAttributeSet) const
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
		[this, Tag](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeChangedMessage(Tag, Data.NewValue);
		}
	);
	BroadcastAttributeChangedMessage(Tag, Attribute.GetNumericValue(ChaosAttributeSet));
}

void AChaosPlayerState::BroadcastAttributeChangedMessage(const FGameplayTag& Tag, const float NewValue) const
{
	FAttributeChangedMessage AttributeChangedMessage;
	AttributeChangedMessage.NewValue = NewValue;

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(Tag, AttributeChangedMessage);
}


