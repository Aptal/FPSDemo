// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterUserWidget.generated.h"


class UCanvasPanel;

UCLASS()
class SHOOTDEMO_API UShooterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UShooterUserWidget(const FObjectInitializer& objectInitializer);

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	/** ���µ���ʱ */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateCountdown(const int32 RemainingTime);

	/** ������ҵ�ǰ���� */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePlayerScore(const int32& PlayerScore);

	/** ��ʾ������� */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowScorePanel(const TArray<int32>& PlayerScores);

protected:
	/** ������ʾ����ʱ���ı� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CountdownText;

	/** ������ʾ��ҷ������ı� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlayerScoreText;

	/** ������ʾ�÷��������� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ScorePanel;
	
	UCanvasPanel* rootPanel;
};
