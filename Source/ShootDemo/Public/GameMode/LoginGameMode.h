// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"

class ULoginUserWidget;

UCLASS()
class SHOOTDEMO_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALoginGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
public:

	//UPROPERTY()
	//TObjectPtr<ULoginUserWidget> LoginWidgetInstance;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LoginWidget")
	//TSubclassOf<class ULoginUserWidget> WidgetClass;
};
