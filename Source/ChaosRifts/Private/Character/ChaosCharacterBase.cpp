// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ChaosCharacterBase.h"

#include "AbilitySystemComponent.h"

// Sets default values
AChaosCharacterBase::AChaosCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AChaosCharacterBase::InitAbilityActorInfo()
{
}

void AChaosCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AChaosCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
