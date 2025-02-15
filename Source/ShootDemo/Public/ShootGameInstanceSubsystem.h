// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ShootGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTDEMO_API UShootGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UShootGameInstanceSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void Print(FString message, FColor color = FColor::MakeRandomColor(), float showTime = 2.0f, int32 inKey = -1);

	void CreateServer(FString ServerName, FString _ServerPath);

	void FindServer(FString ServerName);

	UFUNCTION(BlueprintCallable, Category = "Screen")
	void SetGameScreen(float x, float y);


protected:
	// 线程安全的Shared_ptr实现
	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionCompleted(FName SessionName, bool WasSuccessful);

	void OnDestroySessionCompleted(FName SessionName, bool WasSuccessful);

	void OnFindSessionCompleted(bool WasSuccessful);

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	bool bCreateServerAfterDestroy;
	FString DestroyServerName;
	FString ServerNameToFind;
	FString ServerPath;
	FName MySessionName;
	// 查询会话对象
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
