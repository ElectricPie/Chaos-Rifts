// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ChaosProjectileSpell.h"

#include "AbilitySystemComponent.h"
#include "Actor/ChaosProjectile.h"
#include "Interaction/CombatInterface.h"

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

	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface == nullptr)
		return;
	
	const FVector SocketLocation = CombatInterface->GetWeaponSocketLocation();
	FRotator Rotation = (TargetLocation - SocketLocation).Rotation();
	Rotation.Pitch = 0.f;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

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
