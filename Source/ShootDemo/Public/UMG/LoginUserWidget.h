// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

class UButton;
class UEditableTextBox;

UCLASS()
class SHOOTDEMO_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ULoginUserWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnLoginButtonClicked();

	UFUNCTION()
	void OnRegisterButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> LoadingWidget;
	
protected:
	virtual void NativeConstruct() override;

	// 工具函数: 检查数据文件是否存在
	bool CheckTextFileExists(FString FileName);
	// 工具函数: 将数据存入文本文件
	bool SaveToTextFile(FString FileName);
	// 工具函数: 从文本文件读取数据
	bool LoadFromTextFile(FString FileName);
	
private:

	void LoadNextLevel();

	UButton* LoginButton;
	UButton* RegisterButton;

	UEditableTextBox* UsernameTextBox;
	UEditableTextBox* PasswordTextBox;

	FString Username;
	FString Password;
};
