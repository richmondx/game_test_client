#include "GamePlatformPluginPrivatePCH.h"
#include "ClientWorker.h"

FClientWorker* FClientWorker::runnableWorker = nullptr;

FClientWorker::FClientWorker(FSocket* socket, TQueue<TArray<uint8>>* clientMessages, TQueue<TArray<uint8>>* serviceMessages, ABaseGamePlatformClientPlayerController* pc) {
	clientSocket = socket;
	clientWorkerStatus = EClientWorkerStatus::EC_WORKER_UNINITIALIZED;
	messageToClient = clientMessages;
	messageFromClient = serviceMessages;
	playerController = pc;
	playerController->SetClientStatus(clientWorkerStatus);
	runnableThread = FRunnableThread::Create(this, TEXT("FClientWorker"));
	
}



FClientWorker * FClientWorker::StartClientWorker(FSocket* socket, TQueue<TArray<uint8>>* msgToClient, TQueue<TArray<uint8>>* msgFromClient, ABaseGamePlatformClientPlayerController* pc)
{
	if (runnableWorker == nullptr && FPlatformProcess::SupportsMultithreading()) {
		runnableWorker = new FClientWorker(socket, msgToClient, msgFromClient, pc);
	}
	return runnableWorker;
}

uint32 FClientWorker::Run() {
	if (clientWorkerStatus != EClientWorkerStatus::EC_WORKER_INITIALIZED) return 1;
	clientWorkerStatus = EClientWorkerStatus::EC_WORKER_STARTING;
	playerController->SetClientStatus(clientWorkerStatus);
	FPlatformProcess::Sleep(0.03);
	clientWorkerStatus = EClientWorkerStatus::EC_WORKER_RUNNING;
	playerController->SetClientStatus(clientWorkerStatus);
	while (clientWorkerStatus == EClientWorkerStatus::EC_WORKER_RUNNING) {
		FPlatformProcess::Sleep(0.03);
	}
	clientWorkerStatus = EClientWorkerStatus::EC_WORKER_INITIALIZED;
	playerController->SetClientStatus(clientWorkerStatus);
	return 0;
}
void FClientWorker::Stop() {
	clientWorkerStatus = EClientWorkerStatus::EC_WORKER_STOPPING;
	playerController->SetClientStatus(clientWorkerStatus);
};
void FClientWorker::StopClientWorker() {
	if (runnableWorker != nullptr)
	{
		runnableWorker->StopRunnable();
		delete runnableWorker;
		runnableWorker = nullptr;
	}
}
void FClientWorker::StopRunnable() {
	Stop();
	runnableThread->WaitForCompletion();
}