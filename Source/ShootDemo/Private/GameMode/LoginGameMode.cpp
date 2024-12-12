// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LoginGameMode.h"
#include "UMG/LoginUserWidget.h"

ALoginGameMode::ALoginGameMode()
	: Super()
{

}

void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALoginGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//if (WidgetClass)
	//{
	//	LoginWidgetInstance = CreateWidget<ULoginUserWidget>(GetWorld(), WidgetClass);
	//	if (LoginWidgetInstance != nullptr)
	//	{
	//		LoginWidgetInstance->AddToViewport(3);
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("add success")));
	//	}
	//	else
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("create error")));
	//	}
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("init error")));
	//}

}
