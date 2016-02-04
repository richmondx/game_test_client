#pragma once

#include "ThreadingBase.h"
#include "clientWorkerStatus.h"
#include "BaseGamePlatformClientPlayerController.h"



class FClientWorker : public FRunnable {

		static FClientWorker* runnableWorker;
		FRunnableThread* runnableThread;
		FSocket* clientSocket;
		EClientWorkerStatus clientWorkerStatus;
		TQueue<TArray<uint8>>* messageToClient;
		TQueue<TArray<uint8>>* messageFromClient;
		ABaseGamePlatformClientPlayerController* playerController;
		void StopRunnable();

public:
	FClientWorker(FSocket* socket, TQueue<TArray<uint8>>* messageToClient, TQueue<TArray<uint8>>* messagesFromClient, ABaseGamePlatformClientPlayerController* pc);
	static FClientWorker* StartClientWorker(FSocket* socket, TQueue<TArray<uint8>>* msgToClient, TQueue<TArray<uint8>>* msgFromClient, ABaseGamePlatformClientPlayerController* pc);
	static void StopClientWorker();
	// Begin FRunnable interface.
	virtual bool Init() {
		clientWorkerStatus = EClientWorkerStatus::EC_WORKER_INITIALIZED;
		//playerController->SetClientStatus(clientWorkerStatus);
		return true;

	};
	virtual uint32 Run();
	virtual void Stop();
	EClientWorkerStatus GetClientStatus() {
		return clientWorkerStatus;
	};
};
