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

	/** 更新倒计时 */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateCountdown(const int32 RemainingTime);

	/** 更新玩家当前分数 */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePlayerScore(const int32& PlayerScore);

	/** 显示分数面板 */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowScorePanel(const TArray<int32>& PlayerScores);

protected:
	/** 用于显示倒计时的文本 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CountdownText;

	/** 用于显示玩家分数的文本 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlayerScoreText;

	/** 用于显示得分面板的容器 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ScorePanel;
	
	UCanvasPanel* rootPanel;
};
