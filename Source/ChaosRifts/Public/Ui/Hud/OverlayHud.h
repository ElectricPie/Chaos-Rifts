// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OverlayHud.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class CHAOSRIFTS_API AOverlayHud : public AHUD
{
	GENERATED_BODY()

public:
	void InitializeOverlay();
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUserWidget> OverlayWidget;
};
