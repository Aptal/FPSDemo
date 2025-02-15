// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootGameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "Online/OnlineSessionNames.h"

UShootGameInstanceSubsystem::UShootGameInstanceSubsystem()
{
	bCreateServerAfterDestroy = false;
	DestroyServerName = "";
	ServerNameToFind = "";
	MySessionName = FName("");
	ServerPath = "";

}

void UShootGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SetGameScreen(720, 480);
	Print("Subsystem Init");

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		FString SystemName = Subsystem->GetSubsystemName().ToString();
		Print(SystemName);

		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			Print("SessionInterface is valid");
			// 会话创建完成回调
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UShootGameInstanceSubsystem::OnCreateSessionCompleted);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UShootGameInstanceSubsystem::OnDestroySessionCompleted);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UShootGameInstanceSubsystem::OnFindSessionCompleted);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UShootGameInstanceSubsystem::OnJoinSessionCompleted);
		}
	}
}

void UShootGameInstanceSubsystem::Deinitialize()
{
	Print("Subsystem DeInit");
}

void UShootGameInstanceSubsystem::Print(FString message, FColor color, float showTime, int32 inKey)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(inKey, showTime, color, message);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
}

void UShootGameInstanceSubsystem::CreateServer(FString ServerName, FString _ServerPath)
{
	if (ServerName.IsEmpty())
	{
		Print("Server Name Cannot be Empty");
		return;
	}

	ServerPath = _ServerPath;
	MySessionName = FName("MultiFPS Session");
	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(MySessionName);
	if (ExistingSession)
	{
		Print("session exit  destory");
		bCreateServerAfterDestroy = true;
		DestroyServerName = ServerName;
		SessionInterface->DestroySession(MySessionName);
		return;
	}

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPrivateConnections = 10;
	//SessionSettings.bUseLobbiesVoiceChatIfAvailable = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;

	bool isLan = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		isLan = true;
	}
	SessionSettings.bIsLANMatch = isLan;
	// 将服务器名字存入session
	SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UShootGameInstanceSubsystem::OnCreateSessionCompleted(FName SessionName, bool WasSuccessful)
{
	if (!WasSuccessful)
	{
		Print("Session create failed");
		return;
	}
	//"/Game/_GAME/Maps/MainLevel?listen"
	GetWorld()->ServerTravel(ServerPath);
}

void UShootGameInstanceSubsystem::FindServer(FString ServerName)
{
	if (ServerName.IsEmpty())
	{
		Print("Server Name not found");
		return;
	}
	Print(ServerName);

	SessionSearch =  MakeShareable(new FOnlineSessionSearch());
	bool IsLan = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLan = true;
	}
	SessionSearch->bIsLanQuery = IsLan;
	SessionSearch->MaxSearchResults = 9999;
	
	ServerNameToFind = ServerName;

	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

}

void UShootGameInstanceSubsystem::OnFindSessionCompleted(bool WasSuccessful)
{
	if (WasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;

		FOnlineSessionSearchResult* CurrentResult = nullptr;

		Print(FString::Printf(TEXT("Find %d sessions"), Results.Num()));
		if (Results.Num() > 0)
		{
			for (FOnlineSessionSearchResult Result : Results)
			{
				if (Result.IsValid())
				{
					FString retServerName = "None";
					Result.Session.SessionSettings.Get(FName("SERVER_NAME"), retServerName);
					Print(FString::Printf(TEXT("Find server name : %s"), *retServerName),FColor::Red, 5);
					if (ServerNameToFind.Equals(retServerName))
					{
						Print("Find / join success", FColor::Green, 5);
						CurrentResult = &Result;
						break;
					}
				}
			}
		}

		if (CurrentResult)
		{
			SessionInterface->JoinSession(0, MySessionName, *CurrentResult);
		}
	}
	else
	{
		Print("OnFindSessionCompleted failed");
	}
}

void UShootGameInstanceSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		FString Address = "";
		// 根据SessionName 得到ip地址
		bool bSuccess = SessionInterface->GetResolvedConnectString(MySessionName, Address);
		if (bSuccess)
		{
			APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
			if (PC)
			{
				Print("Join Game success");
				PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
			else
			{
				Print("Join no pc");
			}
		}
		else
		{
			Print("join unsuccess");
		}
	}
}

void UShootGameInstanceSubsystem::OnDestroySessionCompleted(FName SessionName, bool WasSuccessful)
{
	if (bCreateServerAfterDestroy)
	{
		bCreateServerAfterDestroy = false;
		CreateServer(DestroyServerName, ServerPath);
	}
}

void UShootGameInstanceSubsystem::SetGameScreen(float x, float y)
{
	UGameUserSettings* userSettings = GEngine->GetGameUserSettings();
	userSettings->SetScreenResolution(FIntPoint(x, y));
	userSettings->SetFullscreenMode(EWindowMode::Windowed);
	userSettings->ApplySettings(true);
}
