// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "ShootDemoGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

class UGameplayStatics;
class ABaseCube;
class AShootDemoCharacter;

UCLASS(minimalapi)
class AShootDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootDemoGameMode();

	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	//尝试生成玩家的Pawn。
	virtual void RestartPlayer(AController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;

	UFUNCTION(BlueprintCallable, Category = "LanGame")
	void HostLanGame();

	UFUNCTION(BlueprintCallable, Category = "LanGame")
	void JoinLanGame(FString address);

	UFUNCTION()
	virtual void PlayerDied(ACharacter* Character);

	//要绑定委托的签名。
	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;

public:
	virtual void Tick(float DeltaTime) override;

	void UpdateCountdown();

	void EndGame();

	/*UFUNCTION(NetMulticast, Reliable)
	void MulticastShowScorePanel(AShootDemoCharacter* Character);
	void MulticastShowScorePanel_Implementation(AShootDemoCharacter* Character);*/

	FTimerHandle TH_CountDown;

};



