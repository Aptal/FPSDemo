// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/LoginUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

ULoginUserWidget::ULoginUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LoginButton = nullptr;
	RegisterButton = nullptr;
	UsernameTextBox = nullptr;
	PasswordTextBox = nullptr;
}

void ULoginUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("ULoginWidget::NativeConstruct()"));

    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("LoginButton")))
    {
        LoginButton = SBtn;

        LoginButton->OnClicked.AddDynamic(this, &ULoginUserWidget::OnLoginButtonClicked);
    }
    if (UButton* SBtn = Cast<UButton>(GetWidgetFromName("RegisterButton")))
    {
        RegisterButton = SBtn;

        RegisterButton->OnClicked.AddDynamic(this, &ULoginUserWidget::OnRegisterButtonClicked);
    }
    if (UEditableTextBox* SText = Cast<UEditableTextBox>(GetWidgetFromName("UsernameTextBox")))
    {
        UsernameTextBox = SText;
    }
    if (UEditableTextBox* SText = Cast<UEditableTextBox>(GetWidgetFromName("PasswordTextBox")))
    {
        PasswordTextBox = SText;
    }
}

void ULoginUserWidget::OnLoginButtonClicked()
{
    if (UsernameTextBox == nullptr || PasswordTextBox == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget can't get"));
        return;
    }

    FText UsernameText = UsernameTextBox->GetText();
    FText PasswordText = PasswordTextBox->GetText();
    FString UsernameStr = UsernameText.ToString();
    FString PasswordStr = PasswordText.ToString();

    if (UsernameStr.Len() <= 0 || PasswordStr.Len() <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Username or Password must not be empty"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Login button clicked"));

    // 示例：切换到对战关卡
    UGameplayStatics::OpenLevel(this, TEXT("FirstPersonMap"));
}

void ULoginUserWidget::OnRegisterButtonClicked()
{
    if (UsernameTextBox == nullptr || PasswordTextBox == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget can't get"));
        return;
    }

    // 获取当前编辑框内的文本内容
    FText UsernameText = UsernameTextBox->GetText();
    FText PasswordText = PasswordTextBox->GetText();
    FString UsernameStr = UsernameText.ToString();
    FString PasswordStr = PasswordText.ToString();
    if (UsernameStr.Len() <= 0 || PasswordStr.Len() <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Username or Password must not be empty"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("register button clicked"));
}

bool ULoginUserWidget::CheckTextFileExists(FString FileName)
{
	return false;
}

bool ULoginUserWidget::SaveToTextFile(FString FileName)
{
	return false;
}

bool ULoginUserWidget::LoadFromTextFile(FString FileName)
{
	return false;
}
