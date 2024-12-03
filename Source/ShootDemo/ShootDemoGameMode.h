// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootDemoGameMode.generated.h"

class UGameplayStatics;
class ABaseCube;

UCLASS(minimalapi)
class AShootDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootDemoGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;

public:
	virtual void Tick(float DeltaTime) override;

	void InitScoreCube();

	void UpdateCountdown();

	void EndGame();

	TMap<FName, int> hitCount;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int importantGoalCount = 3;

	UPROPERTY(EditAnyWhere, category = "Game Info")
	int importantBuff = 2;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, category = "Time Info", meta = (AllowPrivateAccess = "true"))
	int Seconds = 60;

	FTimerHandle TH_CountDown;

	/*TArray<AActor*> ScoreCube;*/

};



