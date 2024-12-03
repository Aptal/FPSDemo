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

	///** ��ҷ�����ͬ�������� */
	////UPROPERTY(ReplicatedUsing = OnRep_Score)
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, category = "Play State score")
	int32 PlayerScore;

public:
	/** ���ӷ������������˵��ã� */
	//UFUNCTION(Server, Reliable, WithValidation)
	void AddScore(int32 ScoreAmount);

	/** �������»ص� */
	void OnRep_Score() override;

	/** ��ȡ��ҷ��� */
	int32 GetPlayerScore() const { return PlayerScore; }
	
};
