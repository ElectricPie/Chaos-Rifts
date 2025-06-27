// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosCharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class CHAOSRIFTS_API AEnemyCharacter : public AChaosCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;
};
