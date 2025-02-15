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

	FVector GetEnemyRandomSpawnLocation();

public:
	UFUNCTION(Server, Reliable)
	void InitScoreCube();
	void InitScoreCube_Implementation();


	UFUNCTION(NetMulticast, Reliable)
	void MulticastCubeBuff(ABaseCube* cube);
	virtual void MulticastCubeBuff_Implementation(ABaseCube* cube);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulticast_SpawnEnemy();
	virtual void NetMulticast_SpawnEnemy_Implementation();

	void EndGame();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastShowScorePanel(AShootDemoCharacter* Character);
	void MulticastShowScorePanel_Implementation(AShootDemoCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void SpawnEnemyies();

	UFUNCTION(BlueprintCallable)
	void OnEnemyDeath();

	void UpdateCountdown();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_GetScoreList();
	void Server_GetScoreList_Implementation();

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantGoalCount = 3;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int ImportantBuff = 2;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AEnemyBase> EnemyClass;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, category = "Game Info")
	int EnemyNumber = 5;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, category = "Game Info")
	int CurEnemyNumber = 0;

	UPROPERTY(ReplicatedUsing = OnRep_Seconds, EditAnyWhere, BluePrintReadWrite, category = "Time Info", meta = (AllowPrivateAccess = "true"))
	int Seconds = 30;

	UPROPERTY(Replicated, EditAnyWhere, BluePrintReadWrite, category = "Game Info")
	TArray<int32> PlayerScores;
	UPROPERTY(Replicated, EditAnyWhere, BluePrintReadWrite, category = "Game Info")
	TArray<FString> PlayerName;
	/*UPROPERTY(Replicated, EditAnyWhere, BluePrintReadWrite, category = "Game Info")
	TMap<int32> PlayerScoresInfo;*/


	//FTimerHandle TH_CountDown;

	UPROPERTY(Replicated)
	TArray<AActor*> ScoreCube;

	// 函数声明，用于处理Seconds变量复制时的回调
	UFUNCTION()
	void OnRep_Seconds();

//protected:
//	mutable TArray<int32> PlayerScores;
};
