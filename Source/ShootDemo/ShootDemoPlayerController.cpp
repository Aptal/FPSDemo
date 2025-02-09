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

	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AShootDemoPlayerController::InitHUDWidget);
	GameInfoHUD = Cast<AShooterHUD>(GetHUD());
	if (GameInfoHUD)
	{
		GameInfoHUD->ShooterController = this;
		GameInfoHUD->initWI();
		GameInfoUI = GameInfoHUD->WidgetInstance;
		GameInfoUI->UpdateHPBar(1.0);
	}
}

void AShootDemoPlayerController::InitHUDWidget()
{
	GameInfoHUD = Cast<AShooterHUD>(GetHUD());
	if (GameInfoHUD)
	{
		GameInfoUI = GameInfoHUD->WidgetInstance;
	}
}

void AShootDemoPlayerController::ChangeCrosshairColorTemporarily()
{
	if (GameInfoUI && IsLocalController())
	{
		GameInfoUI->UpdateCrosshair(FLinearColor::Red);

		// 使用定时器在 1 秒后恢复颜色
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]()
			{
				GameInfoUI->UpdateCrosshair(FLinearColor::Black); // 恢复为默认颜色
			}), 1.0f, false);
	}
}

void AShootDemoPlayerController::ClientChangeCrosshairColor_Implementation()
{
	if (IsLocalController())
	{
		ChangeCrosshairColorTemporarily();
	}
}
