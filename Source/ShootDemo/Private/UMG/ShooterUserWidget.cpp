// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ShooterUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "ShootGameState.h"

UShooterUserWidget::UShooterUserWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	CountdownText = nullptr;
	PlayerScoreText = nullptr;
	AmmoCurrentText = nullptr;
	AmmoMaxText = nullptr;
	TotalScoreText = nullptr;
	CrosshairsImg = nullptr;
	BloodScreen = nullptr;
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

	CrosshairsImg = Cast<UImage>(GetWidgetFromName("CrosshairsImg"));

	BloodScreen = Cast<UImage>(GetWidgetFromName("BloodScreen"));
	if (BloodScreen)
	{
		BloodScreen->SetVisibility(ESlateVisibility::Hidden);
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

void UShooterUserWidget::UpdateHPBar(const float HP)
{
	if (HPBar)
	{
		// HP : CurHealthValue / MaxHealth
		HPBar->SetPercent(HP);
	}
}

void UShooterUserWidget::UpdateAmmoCurrent(const int32 AmmoCurrent)
{
	if (AmmoCurrentText != nullptr)
	{
		AmmoCurrentText->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoCurrent)));
	}
}

void UShooterUserWidget::UpdateAmmoMax(const int32 AmmoMax)
{
	if (AmmoMaxText != nullptr)
	{
		AmmoMaxText->SetText(FText::FromString(FString::Printf(TEXT("%d"), AmmoMax)));
	}
}

void UShooterUserWidget::UpdateCrosshair(const FLinearColor& NewColor)
{
	if (CrosshairsImg)
	{
		CrosshairsImg->SetColorAndOpacity(NewColor);
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

		//TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("All Players Total Scores: %d"), totalScore)));

		ScorePanel->SetVisibility(ESlateVisibility::Visible);
	}
}

void UShooterUserWidget::ShowScorePanel2()
{
	if (ScorePanel)
	{
		int32 totalScore = 0;
		ScoreInfoBox->ClearChildren();

		TObjectPtr<AShootGameState> GS = Cast<AShootGameState>(GetWorld()->GetGameState());
		if (GS)
		{
			for (int32 i = 0; i < GS->PlayerScores.Num(); ++i)
			{
				totalScore += GS->PlayerScores[i];

				UTextBlock* ScoreText = NewObject<UTextBlock>(this);
				if (ScoreText)
				{
					FString PlayerName = (GS->PlayerName.IsValidIndex(i)) ? GS->PlayerName[i] : FString("Player");
					FString ScoreDisplayText = FString::Printf(TEXT("%s: %d"), *PlayerName, GS->PlayerScores[i]);

					ScoreText->SetText(FText::FromString(ScoreDisplayText));
					ScoreInfoBox->AddChildToVerticalBox(ScoreText);
				}
			}

			ScorePanel->SetVisibility(ESlateVisibility::Visible);
		}
	}
}


void UShooterUserWidget::HideScorePanel()
{
	if (ScorePanel)
	{
		ScorePanel->SetVisibility(ESlateVisibility::Hidden);
	}
}
