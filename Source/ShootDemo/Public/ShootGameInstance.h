// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootGameInstance.generated.h"

class UUserWidget;

UCLASS()
class SHOOTDEMO_API UShootGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UShootGameInstance();

	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString &MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);
	
protected:

	/*UPROPERTY()
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UUserWidget> LoadingWidget;*/
	
};
