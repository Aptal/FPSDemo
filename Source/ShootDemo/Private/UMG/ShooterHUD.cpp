// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../ShootDemoPlayerController.h"
#include "ShootPlayerState.h"

void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterHUD::initWI()
{
	if (WidgetClass)
	{
		WidgetInstance = CreateWidget<UShooterUserWidget>(GetWorld(), WidgetClass);
		if (WidgetInstance != nullptr)
		{
			// 参数指定层级，越大越靠上
			WidgetInstance->AddToViewport(3);
		}
	}
}

//void AShooterHUD::UpdateHPBar()
//{
//	AShootPlayerState* PS = Cast<AShootPlayerState>(ShooterController->PlayerState);
//	WidgetInstance->UpdateHPBar(PS->Health / PS->MaxHealth);
//}
