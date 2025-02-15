// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Net/UnrealNetwork.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && HasAuthority())
	{
		BlackboardComponent = AIController->GetBlackboardComponent();
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyBase::EnemyAttached(float DamageAmount)
{
	ServerEnemyAttached(DamageAmount);
	return Health <= 0.0f;
}

bool AEnemyBase::ServerEnemyAttached_Validate(float DamageAmount)
{
	return Health > 0.0f;
}

void AEnemyBase::ServerEnemyAttached_Implementation(float DamageAmount)
{
	//if (GetLocalRole() == ROLE_Authority)
	{ // 仅在服务器端执行
		Health = FMath::Clamp(Health - DamageAmount, 0.0f, 100.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%.1f"), Health));
	}
	if (Health <= 0.0f)
	{
		//MulticastDeathAnmi();
		//Destroy();
	}
}


void AEnemyBase::MulticastDeathAnmi_Implementation()
{
	if (DeathAnimation != nullptr)
	{
		PlayAnimMontage(DeathAnimation);
		
		if (BlackboardComponent) 
		{
			BlackboardComponent->SetValueAsBool("IsDeath", true);
		}
	}
}

bool AEnemyBase::MulticastDeathAnmi_Validate()
{
	return Health <= 0.0f; 
}

void AEnemyBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyBase, Health);
	DOREPLIFETIME(AEnemyBase, IsDamaged);
	//DOREPLIFETIME(AEnemyBase, targetPlayerController);
	DOREPLIFETIME(AEnemyBase, targetPlayer);

}

void AEnemyBase::ResetTarget()
{
	targetPlayer = nullptr;
	IsDamaged = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}
