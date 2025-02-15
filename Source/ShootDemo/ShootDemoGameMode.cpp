// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootDemoGameMode.h"
#include "ShootDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Cube/BaseCube.h"
#include "ShootPlayerState.h"
#include "ShootGameState.h"
#include "ShootDemoPlayerController.h"
#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"
#include "ShootDemoCharacter.h"

AShootDemoGameMode::AShootDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AShooterHUD::StaticClass();

	PlayerStateClass = AShootPlayerState::StaticClass();

	// GameMode仅存在服务端，不能正确调用RPC
	bReplicates = true;
}

void AShootDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &AShootDemoGameMode::PlayerDied);
	}

	GetWorldTimerManager().SetTimer(
		TH_CountDown, 
		this, 
		&AShootDemoGameMode::UpdateCountdown, 1.f, true, 0.0);
}

void AShootDemoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

}

void AShootDemoGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}

void AShootDemoGameMode::PlayerDied(ACharacter* Character)
{
	//获得角色玩家控制器的引用
	AController* CharacterController = Character->GetController();
	AShootDemoCharacter* player = Cast<AShootDemoCharacter>(Character);
	if (player)
	{
		player->RemoveInstanceComponent(player->WeaponComponent);
		player->WeaponComponent = NULL;
	}
	RestartPlayer(CharacterController);
}

void AShootDemoGameMode::InitGameState()
{
	Super::InitGameState();
}

void AShootDemoGameMode::HostLanGame()
{
	// 通过服务器方式进入关卡
	GetWorld()->ServerTravel("Game/_GAME/Maps/MainLevel?listen");
}

void AShootDemoGameMode::JoinLanGame(FString address)
{
	APlayerController* LocalPlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (LocalPlayerController)
	{
		LocalPlayerController->ClientTravel(address, TRAVEL_Absolute);
	}
}

void AShootDemoGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AShootDemoGameMode::InitScoreCube()
//{
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCube::StaticClass(), ScoreCube);
//	//UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("BaseCube"), ScoreCube);
//	//UE_LOG(LogTemp, Warning, TEXT("actors count : %d"), ScoreCube.Num());
//	/*for (AActor* actor : ScoreCube)
//	{
//		TObjectPtr<ABaseCube> cube = Cast<ABaseCube>(actor);
//		if (cube != nullptr)
//		{
//			cube->GetBuff(importantBuff);
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("id : %d"), cube->score));
//
//		}
//	}*/
//
//	ImportantGoalCount = FMath::Clamp(ImportantGoalCount, 0, ScoreCube.Num());
//	TArray<int32> Numbers;
//	for (int32 i = 0; i < ScoreCube.Num(); i++)
//	{
//		Numbers.Add(i);
//	}
//	for (int32 i = 0; i < Numbers.Num(); i++)
//	{
//		int32 RandIndex = FMath::RandRange(i, Numbers.Num() - 1);
//		Numbers.Swap(i, RandIndex);
//	}
//
//	for (int32 i = 0; i < ImportantGoalCount; i++)
//	{
//		if (ABaseCube* cube = Cast<ABaseCube>(ScoreCube[Numbers[i]]))
//		{
//			cube->GetBuff(ImportantBuff);
//		}
//	}
//}

void AShootDemoGameMode::UpdateCountdown()
{
	AShootGameState* GS = GetGameState<AShootGameState>();
	// GameMode仅在服务端，需要主动调用OnRep_Seconds
	//if (HasAuthority())
	{
		GS->Seconds--;
		GS->OnRep_Seconds();
		if (GS->Seconds <= 0)
		{
			GS->EndGame();
			GetWorldTimerManager().ClearTimer(TH_CountDown);
			UGameplayStatics::SetGamePaused(GetWorld(), true);

		}
	}
}

//void AShootDemoGameMode::EndGame()
//{
//	int i = 0;
//	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//	{
//		AShootDemoCharacter* player = Cast<AShootDemoCharacter>(It->Get()->GetCharacter());
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("pc %d"), i++));
//
//		if (player)
//		{
//			MulticastShowScorePanel(player);
//		}
//	}
//	GetWorldTimerManager().ClearTimer(TH_CountDown);
//	UGameplayStatics::SetGamePaused(GetWorld(), true);
//}
//
//void AShootDemoGameMode::MulticastShowScorePanel_Implementation(AShootDemoCharacter* Character)
//{
//	Character->ShowScorePanel();
//}

//void AShootDemoGameMode::OnRep_Seconds()
//{
//	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetWorld()->GetFirstPlayerController());
//	if (PlayerController && PlayerController->GameInfoUI)
//	{
//		PlayerController->GameInfoUI->UpdateCountdown(Seconds);
//	}
//}

//void AShootDemoGameMode::Multicast_SyncSeconds(int NewSeconds)
//{
//	if (HasAuthority())
//	{
//		Seconds = NewSeconds;
//		// 广播给所有客户端（包括本地客户端）
//		//Multicast_SyncSeconds(Seconds);
//		OnRep_Seconds();
//	}
//}
