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
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	///** 玩家分数（同步变量） */
	UPROPERTY(ReplicatedUsing = OnRep_ShootScore, EditAnyWhere, BlueprintReadOnly, category = "Play State score")
	int32 PlayerScore;

public:
	UPROPERTY(ReplicatedUsing = OnRep_UpdateHP, Replicated, VisibleAnywhere, BlueprintReadWrite)
	float Health = 200.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 200.0f;

	/** 增加分数（客户端调用，服务器执行） */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddScore(int32 ScoreAmount);
	void ServerAddScore_Implementation(int32 ScoreAmount);
	bool ServerAddScore_Validate(int32 ScoreAmount);

	/** 分数更新回调 */
	UFUNCTION()
	void OnRep_ShootScore();

	UFUNCTION(BlueprintCallable)
	void OnRep_UpdateHP();

	/** 获取玩家分数 */
	int32 GetPlayerScore() const { return PlayerScore; }
	
};
