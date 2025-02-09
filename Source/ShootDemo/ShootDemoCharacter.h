// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TP_WeaponComponent.h"
#include "ShootDemoCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UTP_WeaponComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AShootDemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ScorePanel;
	
public:
	AShootDemoCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void ShowScorePanel();
	void HideScorePanel();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SpwanProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	// 服务器 RPC 函数，用于在服务器上生成子弹
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpwanProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, const AShootDemoCharacter* SourceCharacter);
	virtual bool ServerSpwanProjectile_Validate(const FVector& SpawnLocation, const FRotator& SpawnRotation, const AShootDemoCharacter* SourceCharacter);
	virtual void ServerSpwanProjectile_Implementation(const FVector& SpawnLocation, const FRotator& SpawnRotation, const AShootDemoCharacter* SourceCharacter);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFireAnmi();
	virtual void MulticastFireAnmi_Implementation();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// 持有武器组件的指针
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UTP_WeaponComponent* WeaponComponent;

	UPROPERTY(ReplicatedUsing = OnRep_AmmoChanged)
	int AmmoCurrent = 0;

	/* 主武器子弹同步start */
	// 复制通知函数
	UFUNCTION()
	void OnRep_AmmoChanged();
	// 多播更新UI
	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastUpdateAmmo();
	/* 主武器子弹同步end */
};

