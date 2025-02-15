// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterUserWidget.generated.h"


class UCanvasPanel;
class UTextBlock;
class UVerticalBox;
class UImage;
class UProgressBar;

UCLASS()
class SHOOTDEMO_API UShooterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UShooterUserWidget(const FObjectInitializer& objectInitializer);

	/** 更新倒计时 */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateCountdown(const int32 RemainingTime);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHPBar(const float HP);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void UpdateAmmoCurrent(const int32 AmmoCurrent);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void UpdateAmmoMax(const int32 AmmoMax);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void UpdateCrosshair(const FLinearColor& NewColor = FLinearColor::White);


	/** 更新玩家当前分数 */
	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void UpdatePlayerScore(const int32& PlayerScore);

	/** 显示分数面板 */
	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void ShowScorePanel(const TArray<int32>& PlayerScores);

	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void ShowScorePanel2();

	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void HideScorePanel();



protected:

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	/** 用于显示倒计时的文本 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CountdownText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HPBar;

	/** 用于显示玩家分数的文本 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerScoreText;

	/** 用于显示得分面板的容器 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* ScorePanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* CrosshairsImg;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TotalScoreText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoCurrentText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoMaxText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* ScoreInfoBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* BloodScreen;
};
