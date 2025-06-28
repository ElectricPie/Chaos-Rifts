// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataDelegate, const FGameplayAbilityTargetDataHandle, TargetData);

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataDelegate ValidData;
	
public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta=(DisplayName="Target Data Under Mouse", DefaultToSelf="OwningAbility", HidePin="OwningAbility", BlueprintInternalUseOnly=true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

protected:
	virtual void Activate() override;

private:
	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
};
