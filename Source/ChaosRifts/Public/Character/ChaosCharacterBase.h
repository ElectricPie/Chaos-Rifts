// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "ChaosCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AChaosCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChaosCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/* Begin CombatInterface */
	virtual FVector GetWeaponSocketLocation() const override;
	/* End CombatInterface */

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<UStaticMeshComponent> EquippedWeaponMesh;
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<UStaticMeshComponent> BackWeaponMesh;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponSocketName = "WeaponSocket";
	UPROPERTY(EditAnywhere, Category="Combat")
	FName BackWeaponSocketName = "BackWeaponSocket";
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName = "TipSocket";
	

protected:
	virtual void InitAbilityActorInfo();
	virtual void InitDefaultAttributes() const;

	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const;

	void AddStartingCharacterAbilities();

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
};
