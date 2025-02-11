// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootDemoPlayerController.generated.h"

class UInputMappingContext;
class AShooterHUD;
class UShooterUserWidget;

/**
 *
 */
UCLASS()
class SHOOTDEMO_API AShootDemoPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

	void InitHUDWidget();

public:

	UFUNCTION()
	void ChangeCrosshairColorTemporarily();

	UFUNCTION(Client, Reliable)
	void ClientChangeCrosshairColor();


	UPROPERTY()
	TObjectPtr<AShooterHUD> GameInfoHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UShooterUserWidget> GameInfoUI;

};
