// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "ShootDemoGameMode.generated.h"

class UGameplayStatics;
class ABaseCube;

UCLASS(minimalapi)
class AShootDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootDemoGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	virtual void Tick(float DeltaTime) override;

	void InitScoreCube();

	void UpdateCountdown();

	void EndGame();

	TMap<FName, int> hitCount;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantGoalCount = 3;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantBuff = 2;

	UPROPERTY(ReplicatedUsing = OnRep_Seconds, EditAnyWhere, BluePrintReadWrite, category = "Time Info", meta = (AllowPrivateAccess = "true"))
	int Seconds = 60;

	FTimerHandle TH_CountDown;

	TArray<AActor*> ScoreCube;

	// 函数声明，用于处理Seconds变量复制时的回调
	UFUNCTION()
	void OnRep_Seconds();

	// 函数声明，用于将服务器的时间同步到客户端
	void Multicast_SyncSeconds(int NewSeconds);
};



