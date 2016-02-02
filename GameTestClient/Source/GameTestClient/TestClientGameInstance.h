// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GamePlatformClient.h"
#include "TestClientGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMETESTCLIENT_API UTestClientGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTestClientGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
		gamePlatformClient = NewObject<UGamePlatformClient>(UGamePlatformClient::StaticClass());
	}

	UFUNCTION(BlueprintCallable, Category = "GamePlatformService")
		UGamePlatformClient* GetPlatformClient() { return gamePlatformClient; };

private:
	UPROPERTY()
	UGamePlatformClient* gamePlatformClient;
	
	
	
};
