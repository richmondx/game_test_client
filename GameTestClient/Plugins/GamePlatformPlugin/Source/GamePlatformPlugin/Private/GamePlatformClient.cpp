#include "GamePlatformPluginPrivatePCH.h"
#include "PlatformClientMessage.h"
#include "GamePlatformClient.h"

bool UGamePlatformClient::ConnectClient(FString address, int32 port, ABaseGamePlatformClientPlayerController* pc) {

	if(platformSocket == nullptr)
		platformSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FIPv4Address::Parse(address, platformAddress);
	auto addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(platformAddress.GetValue());
	addr->SetPort(port);
	bool connection  = platformSocket->Connect(*addr);
	if (connection == true)
	{
		playerController = pc;
		playerController->SetIsClientConnected(connection);
		if (clientWorker == nullptr)
		{
			clientWorker = FClientWorker::StartClientWorker(platformSocket, &messageToClient, &messageFromClient, playerController);
		}
		
	}
	return connection;
	
}
int UGamePlatformClient::SendEchoMessage(FString message) {
	
	FPlatformMessageBlock msgBlock;
	msgBlock.messageData = message;

	FPlatformClientMessage echoMessage;
	echoMessage.messageHeader = 0x00;
	echoMessage.messageBlocks.Insert(msgBlock, 0);


	int32 sent;
	TArray<uint8> msg = echoMessage.GetMessageData();
	platformSocket->Send(msg.GetData(), msg.Num(), sent);
	return sent;
}
bool UGamePlatformClient::DisconnectClient() {
	if (platformSocket == nullptr) return false;
	FClientWorker::StopClientWorker();
	clientWorker = nullptr;
	bool close = platformSocket->Close();
	if (close == true)
	{
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(platformSocket);
	}
	platformSocket = nullptr;
	if (playerController)
		playerController->SetIsClientConnected(false);
	return close;
	
}

TArray<uint8> UGamePlatformClient::GetMessageFromService() {
	if (messageFromClient.IsEmpty() == true)
		return TArray<uint8>();
	TArray<uint8> message;
	messageFromClient.Dequeue(message);
	return message;
}