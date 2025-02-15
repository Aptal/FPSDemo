// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

class UShootGameInstanceSubsystem;

UCLASS()
class SHOOTDEMO_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Subsystem")
	FString ServerName = "TestServer";

protected:

	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadOnly, Category = "Subsystem")
	TObjectPtr<UShootGameInstanceSubsystem> Subsystem;


	UFUNCTION(BlueprintCallable, Category = "BtnClick")
	void OnCreateServerBtnClick(FString CreateServerName, FString ServerPath);

	UFUNCTION(BlueprintCallable, Category = "BtnClick")
	void OnJoinGameBtnClick(FString JoinServerName);

	
};
