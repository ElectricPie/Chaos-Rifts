// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ChaosAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UChaosAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* Vital Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosAttributeSet, Health, COND_None, REPNOTIFY_Always);

	/* Secondary Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UChaosAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosAttributeSet, Health, Health);
}

void UChaosAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosAttributeSet, MaxHealth, MaxHealth);
}
