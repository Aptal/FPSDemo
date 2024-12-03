// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTDEMO_API AShootPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AShootPlayerState();

protected:
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	///** 玩家分数（同步变量） */
	////UPROPERTY(ReplicatedUsing = OnRep_Score)
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, category = "Play State score")
	int32 PlayerScore;

public:
	/** 增加分数（服务器端调用） */
	//UFUNCTION(Server, Reliable, WithValidation)
	void AddScore(int32 ScoreAmount);

	/** 分数更新回调 */
	void OnRep_Score() override;

	/** 获取玩家分数 */
	int32 GetPlayerScore() const { return PlayerScore; }
	
};
