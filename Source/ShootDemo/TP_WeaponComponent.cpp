// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "ShootDemoCharacter.h"
#include "ShootDemoProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "ShootDemoPlayerController.h"
#include "UMG/ShooterUserWidget.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	AmmoMax = 10;
	AmmoCurrent = AmmoMax;

	//SetIsReplicated(true);
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (AmmoCurrent == 0)
	{
		if (EmptySound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EmptySound, Character->GetActorLocation());
		}

		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("rpc: %d"), GetIsReplicated()));

	// 获取生成参数
	AShootDemoPlayerController* PC = Cast<AShootDemoPlayerController>(Character->GetController());
	if (!PC) return;

	const FRotator SpawnRotation = PC->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	if (Character != nullptr)
	{
		Character->SpwanProjectile(SpawnLocation, SpawnRotation);
	}
	

}

// 启用属性复制
void UTP_WeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTP_WeaponComponent, AmmoCurrent);
}

void UTP_WeaponComponent::OnRep_AmmoChanged()
{
	MulticastUpdateAmmo();
}

void UTP_WeaponComponent::MulticastUpdateAmmo_Implementation()
{
	if (AShootDemoPlayerController* PC = Cast<AShootDemoPlayerController>(Character->GetController()))
	{
		PC->GameInfoUI->UpdateAmmoCurrent(AmmoCurrent);
		PC->GameInfoUI->UpdateAmmoMax(AmmoMax);
	}
}

void UTP_WeaponComponent::Reload()
{
}

void UTP_WeaponComponent::UpdateAmmoText(AShootDemoPlayerController* PlayerController)
{
	if (PlayerController && PlayerController->GameInfoUI)
	{
		PlayerController->GameInfoUI->UpdateAmmoMax(AmmoMax);
		PlayerController->GameInfoUI->UpdateAmmoCurrent(AmmoCurrent);
	}
}

bool UTP_WeaponComponent::AttachWeapon(AShootDemoCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	SetIsReplicated(true);
	Character->WeaponComponent = this;
	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);
	
	// Set up action bindings
	if (AShootDemoPlayerController* PlayerController = Cast<AShootDemoPlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}

		UpdateAmmoText(PlayerController);
	}

	return true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}