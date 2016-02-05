// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlatformPluginPrivatePCH.h"
#include "PlatformClientMessage.h"
#include "BaseGamePlatformClientPlayerController.h"

void ABaseGamePlatformClientPlayerController::ProcessMessage(FPlatformClientMessage message) {	
	if (!platformHud)
		platformHud = StaticCast<ABaseGamePlatformClientHUD*>(GetHUD());
	if (platformHud)
	{
		platformHud->ProcessPlatformClientMessage(message);
	}
}
