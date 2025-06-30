// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ChaosPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "ChaosRifts/ChaosRifts.h"
#include "Player/ChaosPlayerState.h"
#include "Ui/Hud/OverlayHud.h"


// Sets default values
AChaosPlayerCharacter::AChaosPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(GetMesh(), "WeaponSocket");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector AChaosPlayerCharacter::GetWeaponTipSocketLocation() const
{
	check(WeaponMesh);
	return WeaponMesh->GetSocketLocation(WeaponTipSocketName);
}

void AChaosPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server Side Initialization
	InitAbilityActorInfo();
	AddStartingCharacterAbilities();
}

void AChaosPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client Side Initialization
	InitAbilityActorInfo();
}

void AChaosPlayerCharacter::InitAbilityActorInfo()
{
	AChaosPlayerState* ChaosPlayerState = GetPlayerState<AChaosPlayerState>();
	check(ChaosPlayerState);
	ChaosPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ChaosPlayerState, this);

	AbilitySystemComponent = ChaosPlayerState->GetAbilitySystemComponent();
	AttributeSet = ChaosPlayerState->GetAttributeSet();

	if (const APlayerController* PlayerController = GetController<APlayerController>())
	{
		if (AOverlayHud* OverlayHud = PlayerController->GetHUD<AOverlayHud>())
		{
			OverlayHud->InitializeOverlay();
		}
	}

	InitDefaultAttributes();

	// TODO: Remove this after testing
	ApplyEffectToSelf(TestEffectClass, 1.f);
}

