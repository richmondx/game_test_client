// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ClientWorkerStatus.h"
#include "Blueprint/UserWidget.h"
#include "BaseGamePlatformClientHUD.generated.h"

/**
 *
 */
UCLASS()
class GAMEPLATFORMPLUGIN_API ABaseGamePlatformClientHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABaseGamePlatformClientHUD(const FObjectInitializer& init) {

	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlatformService")
	TSubclassOf<class UUserWidget> wMessageResponseUI;

	UPROPERTY(BlueprintReadOnly, Category = "GamePlatformService")
	UUserWidget* MessageResponseUI;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "GamePlatformService")
	void SetIsClientConnected(bool is_connected);
	UFUNCTION(BlueprintImplementableEvent, Category = "GamePlatformService")
	void UpdateClientRunStatus(EClientWorkerStatus status);
};
