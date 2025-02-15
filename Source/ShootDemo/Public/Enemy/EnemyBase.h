// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeath);

class UBlackboardComponent;
class AAIController;
class AShootDemoCharacter;

UCLASS()
class SHOOTDEMO_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEnemyDeath OnDeathDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 EnemyScore = 2;

private:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "EnemyState", meta = (AllowPrivateAccess = "true"))
	float Health = 100.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "EnemyState", meta = (AllowPrivateAccess = "true"))
	bool IsDamaged = false;

	//UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "EnemyState", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<AShootDemoPlayerController> targetPlayerController;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "EnemyState", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AShootDemoCharacter> targetPlayer;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBlackboardComponent* BlackboardComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void BPEnemyAttached(float DamageAmount, AShootDemoCharacter* Shooter);

	// 受伤函数
	UFUNCTION(BlueprintCallable, Category = "EnemyState")
	bool EnemyAttached(float DamageAmount);
	// （服务器端执行）
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEnemyAttached(float DamageAmount);
	virtual bool ServerEnemyAttached_Validate(float DamageAmount);
	virtual void ServerEnemyAttached_Implementation(float DamageAmount);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anmi)
	UAnimMontage* DeathAnimation;

	UFUNCTION(NetMulticast, WithValidation, Reliable)
	void MulticastDeathAnmi();
	virtual void MulticastDeathAnmi_Implementation();
	virtual bool MulticastDeathAnmi_Validate();

	// 网络复制设置
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ResetTarget();
};
