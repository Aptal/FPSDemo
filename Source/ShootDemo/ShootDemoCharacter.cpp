// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootDemoCharacter.h"
#include "ShootDemoProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "ShootPlayerState.h"
#include "ShootDemoPlayerController.h"
#include "UMG/ShooterUserWidget.h"
#include "ShootGameState.h"
#include "ShootDemoGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Enemy/EnemyBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AShootDemoCharacter

AShootDemoCharacter::AShootDemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	TP_Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_Body"));
	TP_Body->SetupAttachment(RootComponent);
	TP_Body->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	TP_Body->SetRelativeLocation(FVector(0.f, 0.f, -90.f));

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AmmoCurrent = 0;
	bReplicates = true;
}

void AShootDemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////// Input

void AShootDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootDemoCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootDemoCharacter::Look);

		EnhancedInputComponent->BindAction(IA_ScorePanel, ETriggerEvent::Started, this, &AShootDemoCharacter::ShowScorePanel);
		EnhancedInputComponent->BindAction(IA_ScorePanel, ETriggerEvent::Completed, this, &AShootDemoCharacter::HideScorePanel);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
	//PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AShootDemoCharacter::CallRestartPlayer);
}

void AShootDemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AShootDemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShootDemoCharacter::ShowScorePanel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("press")));

	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetController());
	if (PlayerController && GetWorld() != nullptr)
	{
		if (PlayerController->GameInfoUI)
		{
			PlayerController->bShowMouseCursor = true;

			// 切换输入模式为 UI 交互模式
			FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			//GetWorld()->GetAuthGameMode()->GetGameState();
			//TObjectPtr<AShootGameState> GS = Cast<AShootGameState>(GetWorld()->GetGameState());
			//GS->Server_GetScoreList();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, PlayerController->GetName());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("list size %d"), GS->PlayerScores.Num()));
			//PlayerController->GameInfoUI->ShowScorePanel(GS->PlayerScores);
			PlayerController->GameInfoUI->ShowScorePanel2();
		}
	}
}

void AShootDemoCharacter::HideScorePanel()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("release")));

	TObjectPtr<AShootDemoPlayerController> PlayerController = Cast<AShootDemoPlayerController>(GetController());
	if (PlayerController)
	{
		if (PlayerController->GameInfoUI)
		{
			PlayerController->GameInfoUI->HideScorePanel();
		}
	}
}

void AShootDemoCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AShootDemoCharacter, AmmoCurrent);
}

void AShootDemoCharacter::Destroyed()
{
	Super::Destroyed();

	//绑定至GameMode中的OnPlayerDied事件
	if (UWorld* World = GetWorld())
	{
		if (AShootDemoGameMode* GameMode = Cast<AShootDemoGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void AShootDemoCharacter::CallRestartPlayer(AEnemyBase* Enemy)
{
	// 获得Pawn控制器的引用。
	AController* CortollerRef = GetController();

	/*AmmoCurrent = 0;
	OnRep_AmmoChanged();*/
	if (WeaponComponent)
	{
		RemoveInstanceComponent(WeaponComponent);
	}
	//WeaponComponent->Character = nullptr;
	//WeaponComponent = NULL;
	Enemy->ResetTarget();

	//销毁玩家
	Destroy();

	//在世界中获得World和GameMode，以调用其重启玩家函数。
	if (UWorld* World = GetWorld())
	{
		if (AShootDemoGameMode* GameMode = Cast<AShootDemoGameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(CortollerRef);
		}
	}
}

void AShootDemoCharacter::ServerReload_Implementation()
{
	if (WeaponComponent)
	{
		AmmoCurrent = WeaponComponent->AmmoMax;
		if (HasAuthority())
		{
			if (Cast<AShootDemoPlayerController>(GetController())->IsLocalController())
			{
				OnRep_AmmoChanged();
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("no gun")));
	}
}

void AShootDemoCharacter::OnRep_AmmoChanged()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("ammo changed %d"), AmmoCurrent));

	if (WeaponComponent != nullptr)
	{
		if (AShootDemoPlayerController* PC = Cast<AShootDemoPlayerController>(GetController()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, PC->GetName());
			if (PC->GameInfoUI)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("ammo update %d"), AmmoCurrent));
				PC->GameInfoUI->UpdateAmmoCurrent(AmmoCurrent);
				PC->GameInfoUI->UpdateAmmoMax(WeaponComponent->AmmoMax);
			}
		}
	}
}

void AShootDemoCharacter::SpwanProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	ServerSpwanProjectile(SpawnLocation, SpawnRotation, this);
}

void AShootDemoCharacter::ServerSpwanProjectile_Implementation(const FVector& SpawnLocation, const FRotator& SpawnRotation, const AShootDemoCharacter* SourceCharacter)
{
	if (WeaponComponent != nullptr && WeaponComponent->ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			AShootDemoPlayerController* PlayerController = Cast<AShootDemoPlayerController>(GetController());

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			AShootDemoProjectile* Projectile = World->SpawnActor<AShootDemoProjectile>(WeaponComponent->ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (Projectile)
			{
				AmmoCurrent--;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, PlayerController->GetName());

				if (HasAuthority())
				{
					// 区分客户端、服务端更新UI
					if (PlayerController->IsLocalController())
					{
						OnRep_AmmoChanged();
					}
				}
				Projectile->SetInstigator(this);
				MulticastFireAnmi();
			}
		}
	}
}

void AShootDemoCharacter::MulticastFireAnmi_Implementation()
{
	// Try and play the sound if specified
	if (WeaponComponent->FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, WeaponComponent->FireSound, GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (WeaponComponent->FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(WeaponComponent->FireAnimation, 1.f);
		}
	}
}

bool AShootDemoCharacter::ServerSpwanProjectile_Validate(const FVector& SpawnLocation, const FRotator& SpawnRotation, const AShootDemoCharacter* SourceCharacter)
{
	return AmmoCurrent > 0;
}