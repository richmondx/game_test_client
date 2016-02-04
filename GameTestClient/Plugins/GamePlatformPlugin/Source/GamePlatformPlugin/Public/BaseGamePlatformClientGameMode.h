#pragma once

#include "GameFramework/GameMode.h"
#include "BaseGamePlatformClientHUD.h"
#include "BaseGamePlatformClientGameMode.generated.h"

UCLASS()
class GAMEPLATFORMPLUGIN_API ABaseGamePlatformClientGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ABaseGamePlatformClientGameMode(const FObjectInitializer& init) {
		HUDClass = ABaseGamePlatformClientHUD::StaticClass();
	}


};
