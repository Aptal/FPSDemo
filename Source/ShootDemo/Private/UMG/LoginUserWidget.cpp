// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/LoginUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TimerManager.h"
#include "ShootGameInstance.h"

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

    UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

    //UShootGameInstance* ShootGameInstance = Cast<UShootGameInstance>(UGameplayStatics::GetGameInstance(this));
    //if (ShootGameInstance)
    //{
    //    FString MapName = TEXT("/Game/FirstPerson/Maps/FirstPersonMap.FirstPersonMap");
    //    UE_LOG(LogTemp, Warning, TEXT("Attempting to load level: %s"), *MapName);

    //    ShootGameInstance->BeginLoadingScreen(TEXT("/Game/FirstPerson/Maps/FirstPersonMap.FirstPersonMap"));
    //    UGameplayStatics::OpenLevel(this, *MapName);

    //    /*ShootGameInstance->BeginLoadingScreen(TEXT("ThirdPersonMap"));*/
    //}

    if (LoadingWidgetClass) // LoadingWidgetClass 是 UUserWidget 的子类，需要事先设置
    {
        LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
        if (LoadingWidget)
        {
            LoadingWidget->AddToViewport(10);
        }
    }

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULoginUserWidget::LoadNextLevel, 3.0f, false);

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

void ULoginUserWidget::LoadNextLevel()
{
    UGameplayStatics::OpenLevel(this, TEXT("FirstPersonMap"));
}
