#pragma once

#include "GameFramework/PlayerController.h"
#include "BaseGamePlatformClientHUD.h"
#include "BaseGamePlatformClientPlayerController.generated.h"

/**
 *
 */
UCLASS()
class GAMEPLATFORMPLUGIN_API ABaseGamePlatformClientPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ABaseGamePlatformClientHUD* platformHud;

public:
	void SetIsClientConnected(bool is_connected) { 
		if (!platformHud)
			platformHud = StaticCast<ABaseGamePlatformClientHUD*>(GetHUD());
		if(platformHud)
			platformHud->SetIsClientConnected(is_connected); 
	};
	void SetClientStatus(EClientWorkerStatus status) {
		if(!platformHud)
			platformHud = StaticCast<ABaseGamePlatformClientHUD*>(GetHUD());
		if(platformHud)
			platformHud->UpdateClientRunStatus(status);
	}


};
