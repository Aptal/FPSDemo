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
class AEnemyBase;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AShootDemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* TP_Body;

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

	//������Ϸ�����б�����ʱ���á�
	virtual void Destroyed();

	//����GameMode��������������ҽ�ɫ��
	UFUNCTION(BlueprintCallable)
	void CallRestartPlayer(AEnemyBase* Enemy);

public:
	UFUNCTION(BlueprintCallable)
	void ShowScorePanel();

	UFUNCTION(BlueprintCallable)
	void HideScorePanel();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SpwanProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	// ������ RPC �����������ڷ������������ӵ�
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
	USkeletalMeshComponent* GetTP_Body() const { return TP_Body; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// �������������ָ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	UTP_WeaponComponent* WeaponComponent;
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon")
	void ServerReload();
	virtual void ServerReload_Implementation();


	UPROPERTY(ReplicatedUsing = OnRep_AmmoChanged, BlueprintReadWrite)
	int AmmoCurrent = 0;

	/* �������ӵ�ͬ��start */
	// ����֪ͨ����
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnRep_AmmoChanged();
	// �ಥ����UI
	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastUpdateAmmo();
	/* �������ӵ�ͬ��end */
};

