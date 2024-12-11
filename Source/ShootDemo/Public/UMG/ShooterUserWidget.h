// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterUserWidget.generated.h"


class UCanvasPanel;
class UTextBlock;
class UVerticalBox;

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

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void UpdateAmmoCurrent(const int32 AmmoCurrent);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void UpdateAmmoMax(const int32 AmmoMax);

	/** ������ҵ�ǰ���� */
	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void UpdatePlayerScore(const int32& PlayerScore);

	/** ��ʾ������� */
	UFUNCTION(BlueprintCallable, Category = "PlayerScore")
	void ShowScorePanel(const TArray<int32>& PlayerScores);

protected:
	/** ������ʾ����ʱ���ı� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CountdownText;

	/** ������ʾ��ҷ������ı� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerScoreText;

	/** ������ʾ�÷��������� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ScorePanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoCurrentText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoMaxText;

	UCanvasPanel* rootPanel;
};
