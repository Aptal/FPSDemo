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

	// ���ߺ���: ��������ļ��Ƿ����
	bool CheckTextFileExists(FString FileName);
	// ���ߺ���: �����ݴ����ı��ļ�
	bool SaveToTextFile(FString FileName);
	// ���ߺ���: ���ı��ļ���ȡ����
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
