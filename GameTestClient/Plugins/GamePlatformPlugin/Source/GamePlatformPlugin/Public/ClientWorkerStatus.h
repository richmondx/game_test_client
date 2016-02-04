#pragma once

UENUM(BlueprintType)
enum class EClientWorkerStatus : uint8{
	EC_WORKER_UNINITIALIZED UMETA( DisplayName="Uninitialized"),
	EC_WORKER_INITIALIZED UMETA(DisplayName="Initialized"),
	EC_WORKER_STARTING UMETA(DisplayName = "Starting"),
	EC_WORKER_RUNNING UMETA(DisplayName = "Running"),
	EC_WORKER_STOPPING UMETA(DisplayName = "Stopping")
};
