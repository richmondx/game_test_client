// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlatformPluginPrivatePCH.h"
#include "BaseGamePlatformClientHUD.h"

void ABaseGamePlatformClientHUD::BeginPlay() {
	Super::BeginPlay();
	if (wMessageResponseUI) {
		MessageResponseUI = CreateWidget<UUserWidget>(GetOwningPlayerController(), wMessageResponseUI);
		if (MessageResponseUI)
		{
			MessageResponseUI->AddToViewport();
		}
	}
}
