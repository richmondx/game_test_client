#pragma once
#include "Networking.h"
#include "ClientWorker.h"
#include "BaseGamePlatformClientPlayerController.h"
#include "GamePlatformClient.generated.h"
UCLASS(Blueprintable)
class GAMEPLATFORMPLUGIN_API UGamePlatformClient : public UObject{
  GENERATED_BODY()

public:
	UGamePlatformClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
		platformSocket = nullptr;
		clientWorker = nullptr;
	};
	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	bool ConnectClient(FString address, int32 port, ABaseGamePlatformClientPlayerController* playerController);

	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	bool DisconnectClient();

	UFUNCTION(BlueprintCallable, Category = "GamePlatformService_Messages")
	int SendEchoMessage(FString message);
	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	EClientWorkerStatus GetClientWorkerStatus() {
		if (clientWorker == nullptr)
			return EClientWorkerStatus::EC_WORKER_UNINITIALIZED;
		return clientWorker->GetClientStatus();
	};
	UFUNCTION(BlueprintCallable, Category = "GamePlatformService_Messages")
	int SendAuthenticateMessage(FString username, FString password);
	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
	TArray<uint8> GetMessageFromService();

private:
	ABaseGamePlatformClientPlayerController* playerController;
	TQueue<TArray<uint8>> messageToClient;
	TQueue<TArray<uint8>> messageFromClient;
	FSocket* platformSocket;
	FIPv4Address platformAddress;
	FClientWorker* clientWorker;
};
