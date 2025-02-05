// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootPlayerState.h"
#include "Net/UnrealNetwork.h"

AShootPlayerState::AShootPlayerState()
{
	PlayerScore = 0;

	bReplicates = true;
}

void AShootPlayerState::AddScore(int32 ScoreAmount)
{
	PlayerScore = PlayerScore + ScoreAmount;
}

void AShootPlayerState::OnRep_ShootScore()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player's score updated: %d"), PlayerScore);
}

void AShootPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//if (HasAuthority())
	//{
	//	Health = 500.f;
	//}
}

void AShootPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册同步变量
	DOREPLIFETIME(AShootPlayerState, Health);
	DOREPLIFETIME(AShootPlayerState, PlayerScore);
}