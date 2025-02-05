// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ShootGameState.generated.h"

class ABaseCube;

UCLASS()
class SHOOTDEMO_API AShootGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AShootGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void InitScoreCube();

	void UpdateCountdown();

	TArray<int32>& GetScoreList() const;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantGoalCount = 3;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantBuff = 2;

	UPROPERTY(ReplicatedUsing = OnRep_Seconds, EditAnyWhere, BluePrintReadWrite, category = "Time Info", meta = (AllowPrivateAccess = "true"))
	int Seconds = 30;

	//FTimerHandle TH_CountDown;

	UPROPERTY(Replicated)
	TArray<AActor*> ScoreCube;

	// 函数声明，用于处理Seconds变量复制时的回调
	UFUNCTION()
	void OnRep_Seconds();

protected:
	mutable TArray<int32> PlayerScores;
};
