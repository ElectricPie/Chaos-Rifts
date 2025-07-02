// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ChaosProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ChaosRifts/ChaosRifts.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AChaosProjectile::AChaosProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereTriggerComponent = CreateDefaultSubobject<USphereComponent>("Sphere Trigger Component");
	SphereTriggerComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereTriggerComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereTriggerComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereTriggerComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereTriggerComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereTriggerComponent->SetCollisionObjectType(ECC_Projectile);
	SetRootComponent(SphereTriggerComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void AChaosProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AChaosProjectile::OnSphereOverlapBegin);
	
	SetLifeSpan(LifeSpan);
}

void AChaosProjectile::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		Destroy();
	}
}

