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

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	AmmoMax = 10;
	//SetIsReplicated(true);
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (Character->AmmoCurrent == 0)
	{
		if (EmptySound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EmptySound, Character->GetActorLocation());
		}

		return;
	}

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

void UTP_WeaponComponent::Reload()
{
	if (Character)
	{
		Character->AmmoCurrent = AmmoMax;
		Character->OnRep_AmmoChanged();
	}
}

//void UTP_WeaponComponent::UpdateAmmoText(AShootDemoPlayerController* PlayerController)
//{
//	if (PlayerController && PlayerController->GameInfoUI)
//	{
//		PlayerController->GameInfoUI->UpdateAmmoMax(AmmoMax);
//		PlayerController->GameInfoUI->UpdateAmmoCurrent(AmmoCurrent);
//	}
//}

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
	if (Character->IsLocallyControlled())
	{
		AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	}
	else
	{
		FAttachmentTransformRules AttachmentRule2(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

		AttachToComponent(Character->GetMesh(), AttachmentRule2, FName(TEXT("hand_rSocket")));
	}

	SetIsReplicated(true);
	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);
	Character->WeaponComponent = this;
	Character->AmmoCurrent = AmmoMax;
	Character->OnRep_AmmoChanged();

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

		/*UpdateAmmoText(PlayerController);*/
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