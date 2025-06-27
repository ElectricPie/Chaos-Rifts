// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ChaosProjectileSpell.h"

#include "AbilitySystemComponent.h"
#include "Actor/ChaosProjectile.h"

void UChaosProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UChaosProjectileSpell::SpawnProjectile(const FVector& Location) const
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
		return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Location);

	AChaosProjectile* Projectile = GetWorld()->SpawnActorDeferred<AChaosProjectile>(ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	const UAbilitySystemComponent* SourceAsc = GetAbilitySystemComponentFromActorInfo();
	const FGameplayEffectSpecHandle SpecHandle = SourceAsc->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceAsc->MakeEffectContext());
	
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	Projectile->FinishSpawning(SpawnTransform);
}
