// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosGameplayAbility.h"
#include "ChaosProjectileSpell.generated.h"

class AChaosProjectile;
/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UChaosProjectileSpell : public UChaosGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AChaosProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BLueprintCallable, BlueprintPure=false)
	void SpawnProjectile(const FVector& Location) const;
};
