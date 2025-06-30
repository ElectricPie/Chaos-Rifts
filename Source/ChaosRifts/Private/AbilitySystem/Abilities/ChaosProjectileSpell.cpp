// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ChaosProjectileSpell.h"

#include "AbilitySystemComponent.h"
#include "Actor/ChaosProjectile.h"
#include "Character/ChaosPlayerCharacter.h"

void UChaosProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UChaosProjectileSpell::SpawnProjectile(const FVector& TargetLocation) const
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
		return;

	// TODO: Setup interface for getting socket
	const AChaosPlayerCharacter* PlayerCharacter = Cast<AChaosPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (PlayerCharacter == nullptr)
		return;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(PlayerCharacter->GetWeaponTipSocketLocation());

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
