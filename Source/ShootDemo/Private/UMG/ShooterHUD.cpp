// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass) 
	{
		WidgetInstance = CreateWidget<UShooterUserWidget>(GetWorld(), WidgetClass);
		if (WidgetInstance != nullptr)
		{
			// 参数指定层级，越大越靠上
			WidgetInstance->AddToViewport(3);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("add success")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("create error")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("init error")));
	}

}
