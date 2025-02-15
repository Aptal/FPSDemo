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
#include "Net/UnrealNetwork.h"
#include "Enemy/EnemyBase.h"
#include "../ShootDemoCharacter.h"

AShootGameState::AShootGameState():Super()
{
	bReplicates = true;
}


void AShootGameState::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayTimerHandle;
	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AShootGameState::InitScoreCube, 1.0f, false);

	//if (HasAuthority())
	//{
	//	//GetWorldTimerManager().SetTimer(TH_CountDown, this, &AShootGameState::UpdateCountdown, 1.f, true, 0.0);
	//	InitScoreCube();
	//}
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
	DOREPLIFETIME(AShootGameState, PlayerScores);
	DOREPLIFETIME(AShootGameState, ScoreCube);
	DOREPLIFETIME(AShootGameState, PlayerName);
}

//void AShootGameState::InitScoreCube()
//{
//	
//}

void AShootGameState::InitScoreCube_Implementation()
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
			MulticastCubeBuff(cube);
		}
	}
}

void AShootGameState::MulticastCubeBuff_Implementation(ABaseCube* cube)
{
	cube->GetBuff(ImportantBuff);
}

FVector AShootGameState::GetEnemyRandomSpawnLocation()
{
	float X = FMath::RandRange(2050.f, 2750.f);
	float Y = FMath::RandRange(3000.f, 3300.f);
	float Z = 100.f;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("spawn enemy %.1f %.1f"), X, Y));
	FVector SpawnLocation(X, Y, Z);

	return SpawnLocation;
}

void AShootGameState::NetMulticast_SpawnEnemy_Implementation()
{
	FVector SpawnLocation = GetEnemyRandomSpawnLocation();
	FRotator SpawnRotation = FRotator(0, FMath::RandRange(0.f, 360.f), 0.f);
	AEnemyBase* NewEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, SpawnLocation, SpawnRotation);

	if (NewEnemy)
	{
		// 设置敌人死亡时的回调，确保死亡后会生成新敌人
		NewEnemy->OnDeathDelegate.AddDynamic(this, &AShootGameState::OnEnemyDeath);
	}
}

void AShootGameState::SpawnEnemyies()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("spawn enemy")));
	for (int32 i = 0; i < EnemyNumber; ++i)
	{
		NetMulticast_SpawnEnemy();
	}
}

void AShootGameState::OnEnemyDeath()
{
	NetMulticast_SpawnEnemy();
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

void AShootGameState::Server_GetScoreList_Implementation() 
{
	// TODO: insert return statement here
	if (GetWorld())
	{
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			TObjectPtr<APlayerController> PlayerController = It->Get();
			if (PlayerController)
			{
				PlayerName.Add(PlayerController->GetName());
				TObjectPtr<AShootPlayerState> PlayerState = Cast<AShootPlayerState>(PlayerController->PlayerState);
				if (PlayerState)
				{
					PlayerScores.Add(PlayerState->GetPlayerScore());
				}
			}
		}
	}
}

void AShootGameState::OnRep_Seconds()
{
	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController && PlayerController->GameInfoUI)
	{
		PlayerController->GameInfoUI->UpdateCountdown(Seconds);
	}
}

void AShootGameState::EndGame()
{
	Seconds = 0;
	OnRep_Seconds();
	Server_GetScoreList();
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AShootDemoCharacter* player = Cast<AShootDemoCharacter>(It->Get()->GetCharacter());
	
		if (player)
		{
			MulticastShowScorePanel(player);
		}
	}
}

void AShootGameState::MulticastShowScorePanel_Implementation(AShootDemoCharacter* Character)
{
	Character->ShowScorePanel();
}
