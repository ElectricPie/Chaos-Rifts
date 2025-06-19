// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ChaosAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API UChaosAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UChaosAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
