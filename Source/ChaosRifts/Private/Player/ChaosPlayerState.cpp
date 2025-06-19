// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ChaosPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/ChaosAttributeSet.h"

AChaosPlayerState::AChaosPlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UChaosAttributeSet>(TEXT("AttributeSet"));
}
