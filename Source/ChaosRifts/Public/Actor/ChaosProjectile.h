// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "ChaosProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class CHAOSRIFTS_API AChaosProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
public:
	// Sets default values for this actor's properties
	AChaosProjectile();

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereTriggerComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float LifeSpan = 15.f;

private:
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
