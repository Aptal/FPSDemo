// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"
#include "ShootGameInstanceSubsystem.h"

bool UStartMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		Subsystem = GameInstance->GetSubsystem<UShootGameInstanceSubsystem>();
	}

	return true;
}

void UStartMenuWidget::OnCreateServerBtnClick(FString CreateServerName, FString ServerPath)
{
	if (Subsystem)
	{
		Subsystem->Print("Create Server");
		Subsystem->CreateServer(CreateServerName, ServerPath);
	}
}

void UStartMenuWidget::OnJoinGameBtnClick(FString JoinServerName)
{
	if (Subsystem)
	{
		Subsystem->Print("Join game");
		Subsystem->FindServer(JoinServerName);
	}
}
