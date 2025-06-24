// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ChaosAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FAttributeChangedMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NewValue;
};

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UChaosAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/* Vital Attributes */
	UPROPERTY(BlueprintReadOnly, Category="VitalAttributes", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UChaosAttributeSet, Health)

	/* Secondary Attributes */
	UPROPERTY(BlueprintReadOnly, Category="VitalAttributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UChaosAttributeSet, MaxHealth)

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	/* Vital Attributes */
	UFUNCTION()
	void OnRep_Health();

	/* Secondary Attributes */
	UFUNCTION()
	void OnRep_MaxHealth();
};
