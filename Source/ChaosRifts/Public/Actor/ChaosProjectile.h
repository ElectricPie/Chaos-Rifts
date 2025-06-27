// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "ChaosProjectile.generated.h"

UCLASS()
class CHAOSRIFTS_API AChaosProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChaosProjectile();

	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

};
