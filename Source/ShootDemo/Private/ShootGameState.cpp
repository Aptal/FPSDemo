// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootGameState.h"
#include "../ShootDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Cube/BaseCube.h"
#include "ShootPlayerState.h"
#include "../ShootDemoGameMode.h"
#include "../ShootDemoPlayerController.h"
#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AShootGameState::AShootGameState():Super()
{
	bReplicates = true;
}


void AShootGameState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		//GetWorldTimerManager().SetTimer(TH_CountDown, this, &AShootGameState::UpdateCountdown, 1.f, true, 0.0);
		InitScoreCube();
	}
}

void AShootGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShootGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册同步变量
	DOREPLIFETIME(AShootGameState, Seconds);
}

void AShootGameState::InitScoreCube()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCube::StaticClass(), ScoreCube);

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

//void AShootGameState::UpdateCountdown()
//{
//	/*Seconds--;
//	if (Seconds <= 0)
//	{
//		GetWorldTimerManager().ClearTimer(TH_CountDown);
//	}*/
//	if (HasAuthority()) // 仅服务器执行
//	{
//		Seconds--;
//		if (Seconds <= 0)
//		{
//			GetWorldTimerManager().ClearTimer(TH_CountDown);
//			// 触发游戏结束逻辑（需在GameMode中处理）
//			if (TObjectPtr<AShootDemoGameMode> GM = Cast<AShootDemoGameMode>(GetWorld()->GetAuthGameMode()))
//			{
//				GM->EndGame();
//			}
//		}
//	}
//}

TArray<int32>& AShootGameState::GetScoreList() const
{
	// TODO: insert return statement here
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		TObjectPtr<APlayerController> PlayerController = It->Get();
		if (PlayerController)
		{
			TObjectPtr<AShootPlayerState> PlayerState = Cast<AShootPlayerState>(PlayerController->PlayerState);
			if (PlayerState)
			{
				PlayerScores.Add(PlayerState->GetPlayerScore());  // 假设 PlayerState 有一个 GetScore() 方法
			}
		}
	}
	return const_cast<TArray<int32>&>(PlayerScores);
}

void AShootGameState::OnRep_Seconds()
{
	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController && PlayerController->GameInfoUI)
	{
		PlayerController->GameInfoUI->UpdateCountdown(Seconds);
	}
}
