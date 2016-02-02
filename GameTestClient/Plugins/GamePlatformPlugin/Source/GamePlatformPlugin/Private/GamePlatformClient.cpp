#include "GamePlatformPluginPrivatePCH.h"
#include "GamePlatformClient.h"

bool UGamePlatformClient::ConnectClient(FString address, int32 port) {
	if(platformSocket == nullptr)
		platformSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FIPv4Address::Parse(address, platformAddress);
	auto addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(platformAddress.GetValue());
	addr->SetPort(port);
	return platformSocket->Connect(*addr);
}

bool UGamePlatformClient::DisconnectClient() {
	if (platformSocket == nullptr) return false;
	bool close = platformSocket->Close();
	if (close == true)
	{
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(platformSocket);
	}
	platformSocket = nullptr;
	return close;
	
}