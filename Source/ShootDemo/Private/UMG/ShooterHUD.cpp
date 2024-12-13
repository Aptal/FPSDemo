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
			// ����ָ���㼶��Խ��Խ����
			WidgetInstance->AddToViewport(3);
		}
	}

}
