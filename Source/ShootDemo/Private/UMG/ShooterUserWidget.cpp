// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ShooterUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"

UShooterUserWidget::UShooterUserWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	CountdownText = nullptr;
	PlayerScoreText = nullptr;
	AmmoCurrentText = nullptr;
	AmmoMaxText = nullptr;
	TotalScoreText = nullptr;
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

	if (AmmoCurrentText == nullptr)
	{
		AmmoCurrentText = Cast<UTextBlock>(GetWidgetFromName("AmmoCurrentText"));
	}

	if (AmmoMaxText == nullptr)
	{
		AmmoMaxText = Cast<UTextBlock>(GetWidgetFromName("AmmoMaxText"));
	}

	ScorePanel = Cast<UCanvasPanel>(GetWidgetFromName("ScorePanel"));
	HideScorePanel();

	ScoreInfoBox = Cast<UVerticalBox>(GetWidgetFromName("ScoreInfoBox"));
	TotalScoreText = Cast<UTextBlock>(GetWidgetFromName("TotalScoreText"));

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

void UShooterUserWidget::UpdateAmmoCurrent(const int32 AmmoCurrent)
{
	if (AmmoCurrentText)
	{
		AmmoCurrentText->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoCurrent)));
	}
}

void UShooterUserWidget::UpdateAmmoMax(const int32 AmmoMax)
{
	if (AmmoMaxText)
	{
		AmmoMaxText->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoMax)));
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
		int32 totalScore = 0;
		ScoreInfoBox->ClearChildren();
		for (int32 i = 0; i < PlayerScores.Num(); ++i)
		{
			totalScore += PlayerScores[i];
			UTextBlock* ScoreText = NewObject<UTextBlock>(this);
			if (ScoreText)
			{
				ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Player %d: %d"), i + 1, PlayerScores[i])));
				ScoreInfoBox->AddChildToVerticalBox(ScoreText);
			}
		}

		TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("All Players Total Scores: %d"), totalScore)));

		ScorePanel->SetVisibility(ESlateVisibility::Visible);
	}
}

void UShooterUserWidget::HideScorePanel()
{
	if (ScorePanel)
	{
		ScorePanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
