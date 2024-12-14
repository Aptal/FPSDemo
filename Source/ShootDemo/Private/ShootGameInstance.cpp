// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer.h"

UShootGameInstance::UShootGameInstance()
	:Super()//, LoadingWidgetClass(nullptr), LoadingWidget(nullptr)
{
}

void UShootGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UShootGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UShootGameInstance::EndLoadingScreen);
}

void UShootGameInstance::BeginLoadingScreen(const FString& MapName)
{
	UE_LOG(LogTemp, Warning, TEXT("BeginLoadingScreen"));

	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;

		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;

		/*LoadingWidget = CreateWidget<UUserWidget>(this, LoadingWidgetClass);

		TSharedPtr<SWidget> WidgetPtr = LoadingWidget->TakeWidget();*/

		//LoadingScreen.WidgetLoadingScreen = WidgetPtr;

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UShootGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("EndLoadingScreen"));

	if (!IsRunningDedicatedServer())
	{
		//if (LoadingWidget)
		//{
		//	LoadingWidget->RemoveFromParent();
		//	LoadingWidget = nullptr;
		//	UE_LOG(LogTemp, Warning, TEXT("Loading Screen Removed"));
		//	//LoadingWidget->MarkPendingKill();
		//}
	}
}
