// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosAssetManager.h"

#include "FChaosGameplayTags.h"

UChaosAssetManager& UChaosAssetManager::Get()
{
	check(GEngine)
	return *Cast<UChaosAssetManager>(GEngine->AssetManager);
}

void UChaosAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FChaosGameplayTags::InitializeNativeGameplayTags();
}
