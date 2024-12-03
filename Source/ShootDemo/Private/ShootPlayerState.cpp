// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootPlayerState.h"
#include "Net/UnrealNetwork.h"

AShootPlayerState::AShootPlayerState()
{
}

void AShootPlayerState::AddScore(int32 ScoreAmount)
{
	PlayerScore = PlayerScore + ScoreAmount;

	//OnRep_Score();
}

void AShootPlayerState::OnRep_Score()
{
	UE_LOG(LogTemp, Log, TEXT("Player's score updated: %d"), PlayerScore);
}
//
//void AShootPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	// 注册同步变量
//	DOREPLIFETIME(AShootPlayerState, PlayerScore);
//}