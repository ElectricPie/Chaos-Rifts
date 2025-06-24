// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosCharacterBase.h"
#include "ChaosPlayerCharacter.generated.h"

UCLASS()
class CHAOSRIFTS_API AChaosPlayerCharacter : public AChaosCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChaosPlayerCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> TestEffectClass;
};
