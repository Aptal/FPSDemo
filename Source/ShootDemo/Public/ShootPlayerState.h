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

	UPROPERTY(Replicated, VisibleAnywhere)
	float Health = 200.0f;

public:
	/** ���ӷ������������˵��ã� */
	//UFUNCTION(Server, Reliable, WithValidation)
	void AddScore(int32 ScoreAmount);

	/** �������»ص� */
	UFUNCTION()
	void OnRep_ShootScore();

	/** ��ȡ��ҷ��� */
	int32 GetPlayerScore() const { return PlayerScore; }
	
};
