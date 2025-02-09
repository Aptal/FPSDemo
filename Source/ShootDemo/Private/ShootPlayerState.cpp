// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "../ShootDemoPlayerController.h"
#include "UMG/ShooterUserWidget.h"

AShootPlayerState::AShootPlayerState()
{
	PlayerScore = 0;
	Health = MaxHealth;
	bReplicates = true;
}

void AShootPlayerState::ServerAddScore_Implementation(int32 ScoreAmount)
{
	PlayerScore += ScoreAmount;
	if (HasAuthority() && GetPlayerController()->IsLocalController())
	{
		OnRep_ShootScore();
	}
}
bool AShootPlayerState::ServerAddScore_Validate(int32 ScoreAmount)
{
	return ScoreAmount >= 0;
}

void AShootPlayerState::OnRep_ShootScore()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player's score updated: %d"), PlayerScore);
	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetPlayerController());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player's score updated: %d"), PlayerScore));

	if (PlayerController && PlayerController->GameInfoUI)
	{

		PlayerController->GameInfoUI->UpdatePlayerScore(PlayerScore);
	}
}

void AShootPlayerState::OnRep_UpdateHP()
{
	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetPlayerController());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player's score updated: %d"), PlayerScore));

	if (PlayerController && PlayerController->GameInfoUI)
	{

		PlayerController->GameInfoUI->UpdateHPBar(Health / MaxHealth);
	}
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