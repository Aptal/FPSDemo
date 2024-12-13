// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootDemoPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"

void AShootDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AShootDemoPlayerController::InitHUDWidget);
	
}

void AShootDemoPlayerController::InitHUDWidget()
{
	GameInfoHUD = Cast<AShooterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (GameInfoHUD)
	{
		GameInfoUI = GameInfoHUD->WidgetInstance;
	}
}