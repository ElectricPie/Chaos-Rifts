// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ChaosCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/ChaosAbilitySystemComponent.h"
#include "ChaosRifts/ChaosRifts.h"

// Sets default values
AChaosCharacterBase::AChaosCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	
	BackWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Back Weapon Mesh");
	BackWeaponMesh->SetupAttachment(GetMesh(), FName("BackWeaponSocket"));
	BackWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	EquippedWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	EquippedWeaponMesh->SetupAttachment(GetMesh(), WeaponSocketName);
	EquippedWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector AChaosCharacterBase::GetWeaponSocketLocation() const
{
	
	if (EquippedWeaponMesh->GetStaticMesh())
	{
		return EquippedWeaponMesh->GetSocketLocation(WeaponTipSocketName);
	}

	return GetMesh()->GetSocketLocation(WeaponSocketName);
}

void AChaosCharacterBase::InitAbilityActorInfo()
{
}

void AChaosCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
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

void AChaosCharacterBase::AddStartingCharacterAbilities()
{
	if (!HasAuthority())
		return;

	UChaosAbilitySystemComponent* AbilitySystem = Cast<UChaosAbilitySystemComponent>(GetAbilitySystemComponent());
	AbilitySystem->AddCharacterAbilities(StartingAbilities);
}
