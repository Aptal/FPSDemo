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
	AmmoCurrent = AmmoMax;

	SetIsReplicated(true);
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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("fire 0")));

	// 获取生成参数
	AShootDemoPlayerController* PC = Cast<AShootDemoPlayerController>(Character->GetController());
	if (!PC) return;

	const FRotator SpawnRotation = PC->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	// Try and fire a projectile
	//if (Character->GetLocalRole() < ROLE_Authority)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("fire ----")));

	//	ServerFire(SpawnLocation, SpawnRotation);
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("fire +++++")));

	//	ServerFire(SpawnLocation, SpawnRotation);
	//}
	if (Character != nullptr)
	{
		Character->SpwanProjectile(SpawnLocation, SpawnRotation);
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

//void UTP_WeaponComponent::ActualFire(const FVector& SpawnLocation, const FRotator& SpawnRotation)
//{
//	if (ProjectileClass != nullptr)
//	{
//		UWorld* const World = GetWorld();
//		if (World != nullptr)
//		{
//			AShootDemoPlayerController* PlayerController = Cast<AShootDemoPlayerController>(Character->GetController());
//
//			//Set Spawn Collision Handling Override
//			FActorSpawnParameters ActorSpawnParams;
//			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//			// Spawn the projectile at the muzzle
//			World->SpawnActor<AShootDemoProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//
//			AmmoCurrent--;
//			UpdateAmmoText(PlayerController);
//		}
//	}
//}

//void UTP_WeaponComponent::ServerFire_Implementation(const FVector& SpawnLocation, const FRotator& SpawnRotation)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("fire on Server")));
//
//	ActualFire(SpawnLocation, SpawnRotation);
//}
//
//bool UTP_WeaponComponent::ServerFire_Validate(const FVector& SpawnLocation, const FRotator& SpawnRotation)
//{
//	// 子弹余量
//	return true; // AmmoCurrent > 0;
//}

//// 启用属性复制
//void UTP_WeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(UTP_WeaponComponent, AmmoCurrent);
//}
//
//void UTP_WeaponComponent::OnRep_AmmoChanged()
//{
//	MulticastUpdateAmmo();
//}
//
//void UTP_WeaponComponent::MulticastUpdateAmmo_Implementation()
//{
//	if (AShootDemoPlayerController* PC = Cast<AShootDemoPlayerController>(Character->GetController()))
//	{
//		PC->GameInfoUI->UpdateAmmoCurrent(AmmoCurrent);
//		PC->GameInfoUI->UpdateAmmoMax(AmmoMax);
//	}
//}

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