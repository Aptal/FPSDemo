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

	///** ��ҷ�����ͬ�������� */
	UPROPERTY(ReplicatedUsing = OnRep_ShootScore, EditAnyWhere, BlueprintReadOnly, category = "Play State score")
	int32 PlayerScore;

public:
	UPROPERTY(ReplicatedUsing = OnRep_UpdateHP, Replicated, VisibleAnywhere, BlueprintReadWrite)
	float Health = 200.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 200.0f;

	/** ���ӷ������ͻ��˵��ã�������ִ�У� */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddScore(int32 ScoreAmount);
	void ServerAddScore_Implementation(int32 ScoreAmount);
	bool ServerAddScore_Validate(int32 ScoreAmount);

	/** �������»ص� */
	UFUNCTION()
	void OnRep_ShootScore();

	UFUNCTION(BlueprintCallable)
	void OnRep_UpdateHP();

	/** ��ȡ��ҷ��� */
	int32 GetPlayerScore() const { return PlayerScore; }
	
};
