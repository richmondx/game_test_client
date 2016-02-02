#pragma once
#include "Networking.h"
#include "GamePlatformClient.generated.h"
UCLASS(Blueprintable)
class GAMEPLATFORMPLUGIN_API UGamePlatformClient : public UObject{
  GENERATED_BODY()

public:
	UGamePlatformClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
		platformSocket = nullptr;
	};
	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	bool ConnectClient(FString address, int32 port);

	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	bool DisconnectClient();

private:
	FSocket* platformSocket;
	FIPv4Address platformAddress;
};
