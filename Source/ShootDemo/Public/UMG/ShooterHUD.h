// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUD.generated.h"

class UShooterUserWidget;

UCLASS()
class SHOOTDEMO_API AShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	
protected:
	virtual void BeginPlay() override;

public:

	TObjectPtr<UShooterUserWidget> WidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UserWidget")
	TSubclassOf<class UShooterUserWidget> WidgetClass;

};
