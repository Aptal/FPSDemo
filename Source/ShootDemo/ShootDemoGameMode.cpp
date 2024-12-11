// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootDemoGameMode.h"
#include "ShootDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Cube/BaseCube.h"
#include "ShootPlayerState.h"
#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"
#include "Kismet/GameplayStatics.h"

AShootDemoGameMode::AShootDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AShooterHUD::StaticClass();

	PlayerStateClass = AShootPlayerState::StaticClass();

	bReplicates = true;
}

void AShootDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TH_CountDown, this, &AShootDemoGameMode::UpdateCountdown, 1.f, true, 0.0);
}

void AShootDemoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	InitScoreCube();
}

void AShootDemoGameMode::InitGameState()
{
	Super::InitGameState();

	//UE_LOG(LogTemp, Warning, TEXT("game begin : init cube position and random select Important Goal Cube "));

	//FVector v = FVector(1000,0,0);
	//FRotator r = FRotator(0, 0, 0);
	//   
	//for (int i = 0; i < 5; ++i) {
	//	FVector SpawnLocation = FVector(1000 + i * 100, 1200, 0);  
	//	FRotator SpawnRotation = FRotator(0, 0, 0); 
	//	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	//	ScoreCube.Add(GetWorld()->SpawnActor<ABaseCube>(ABaseCube::StaticClass(), SpawnTransform));
	//}
	/*InitScoreCube();*/
}

void AShootDemoGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册同步变量
	DOREPLIFETIME(AShootDemoGameMode, Seconds);
}

void AShootDemoGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootDemoGameMode::InitScoreCube()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCube::StaticClass(), ScoreCube);
	//UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("BaseCube"), ScoreCube);
	//UE_LOG(LogTemp, Warning, TEXT("actors count : %d"), ScoreCube.Num());
	/*for (AActor* actor : ScoreCube)
	{
		TObjectPtr<ABaseCube> cube = Cast<ABaseCube>(actor);
		if (cube != nullptr)
		{
			cube->GetBuff(importantBuff);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("id : %d"), cube->score));

		}
	}*/

	ImportantGoalCount = FMath::Clamp(ImportantGoalCount, 0, ScoreCube.Num());
	TArray<int32> Numbers;
	for (int32 i = 0; i < ScoreCube.Num(); i++)
	{
		Numbers.Add(i);
	}
	for (int32 i = 0; i < Numbers.Num(); i++)
	{
		int32 RandIndex = FMath::RandRange(i, Numbers.Num() - 1);
		Numbers.Swap(i, RandIndex);
	}

	for (int32 i = 0; i < ImportantGoalCount; i++)
	{
		if (ABaseCube* cube = Cast<ABaseCube>(ScoreCube[Numbers[i]]))
		{
			cube->GetBuff(ImportantBuff);
		}
	}
}

void AShootDemoGameMode::UpdateCountdown()
{
	//if (Seconds != 0)
	//{
	//	Seconds = Seconds - 1;
	//	TObjectPtr<AShooterHUD> m_HUD = Cast<AShooterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//	if (m_HUD)
	//	{
	//		TObjectPtr<UShooterUserWidget> m_UserWidget = Cast<UShooterUserWidget>(m_HUD->WidgetInstance);
	//		if (m_UserWidget)
	//		{
	//			m_UserWidget->UpdateCountdown(Seconds);
	//		}
	//	}
	//}
	//else
	//{
	//	// game over
	//	// 日志打印分数
	//	EndGame();
	//	GetWorldTimerManager().ClearTimer(TH_CountDown);
	//}
	if (HasAuthority())
	{
		Seconds--;
		if (Seconds <= 0)
		{
			EndGame();
		}
		// 通知客户端更新时间显示等
		Multicast_SyncSeconds(Seconds);
	}
}

void AShootDemoGameMode::EndGame()
{

	//FConstPlayerControllerIterator PlayerControllers = GetWorld()->GetPlayerControllerIterator();
	//TArray<APlayerController*> PlayerControllers = GetWorld()->GetPlayerControllerIterator();
	int32 TotalScore = 0;
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		AShootPlayerState* PS = Cast<AShootPlayerState>(pc->PlayerState);
		if (PS != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"), *pc->GetName(), PS->GetPlayerScore());
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("score : %d"), PS->GetPlayerScore()));
		}
	}

	//for (FConstPlayerControllerIterator PlayerControllerIt = GetWorld()->GetPlayerControllerIterator(); PlayerControllerIt; ++PlayerControllerIt)
	//{
	//	TObjectPtr<APlayerController> PC = PlayerControllerIt->Get();
	//	if (PC != nullptr) 
	//	{
	//		if (AShootPlayerState* PS = Cast<AShootPlayerState>(PC->PlayerState))
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("Player %s Score: %d"), *PC->GetName(), PS->GetPlayerScore());
	//			TotalScore += PS->GetPlayerScore();
	//		}
	//	}
	//}

	UE_LOG(LogTemp, Log, TEXT("Total Score: %d"), TotalScore);
}

void AShootDemoGameMode::OnRep_Seconds()
{
	TObjectPtr<AShooterHUD> m_HUD = Cast<AShooterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (m_HUD)
	{
		TObjectPtr<UShooterUserWidget> m_UserWidget = Cast<UShooterUserWidget>(m_HUD->WidgetInstance);
		if (m_UserWidget)
		{
			m_UserWidget->UpdateCountdown(Seconds);
		}
	}
}

void AShootDemoGameMode::Multicast_SyncSeconds(int NewSeconds)
{
	if (HasAuthority())
	{
		Seconds = NewSeconds;
		// 广播给所有客户端（包括本地客户端）
		//Multicast_SyncSeconds(Seconds);
		OnRep_Seconds();
	}
}
