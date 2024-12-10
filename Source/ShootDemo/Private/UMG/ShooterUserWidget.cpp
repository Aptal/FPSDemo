// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ShooterUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

UShooterUserWidget::UShooterUserWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	CountdownText = nullptr;
	PlayerScoreText = nullptr;
}

bool UShooterUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (CountdownText == nullptr)
	{
		CountdownText = Cast<UTextBlock>(GetWidgetFromName("CountdownText"));
	}

	if (PlayerScoreText == nullptr) 
	{
		PlayerScoreText = Cast<UTextBlock>(GetWidgetFromName("PlayerScoreText"));
	}

	return true;
}

void UShooterUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UShooterUserWidget::UpdateCountdown(const int32 RemainingTime)
{
	if (CountdownText)
	{
		CountdownText->SetText(FText::FromString(FString::Printf(TEXT("Count Down: %d"), RemainingTime)));
	}
}

void UShooterUserWidget::UpdatePlayerScore(const int32& PlayerScore)
{
	if (PlayerScoreText)
	{
		PlayerScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), PlayerScore)));
	}
}

void UShooterUserWidget::ShowScorePanel(const TArray<int32>& PlayerScores)
{
	if (ScorePanel)
	{
		ScorePanel->ClearChildren();
		for (int32 i = 0; i < PlayerScores.Num(); ++i)
		{
			UTextBlock* ScoreText = NewObject<UTextBlock>(this);
			if (ScoreText)
			{
				ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Player %d: %d"), i + 1, PlayerScores[i])));
				ScorePanel->AddChildToVerticalBox(ScoreText);
			}
		}
	}
}
