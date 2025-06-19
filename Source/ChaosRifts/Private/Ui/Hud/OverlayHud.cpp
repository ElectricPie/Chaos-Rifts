// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/Hud/OverlayHud.h"

#include "Blueprint/UserWidget.h"

void AOverlayHud::InitializeOverlay()
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is null, please fill out OverlayHud blueprint"));
	OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}
