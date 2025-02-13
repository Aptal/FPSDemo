// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

const float ANonPlayerCharacter::FATIGUE_THRESHOLD = 100.0f;

ANonPlayerCharacter::ANonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//UCharacterMovementComponent* npcCharacterMovement = GetCharacterMovement();
	//if (npcCharacterMovement)
	//{
	//	npcCharacterMovement->MaxWalkSpeed = 100.0f;
	//}
	
}

void ANonPlayerCharacter::ResetFatigue()
{
    Fatigue = 0.0; 
    bIsRest = false;
    
}

void ANonPlayerCharacter::StartResting()
{
    bIsRest = true;
    //GetCharacterMovement()->MaxWalkSpeed = 0.0f;

    float RestTime = FMath::RandRange(7.0f, 15.0f);

    //GetWorldTimerManager().SetTimer(
    //    RestTimerHandle,
    //    [this]()
    //    {
    //        Fatigue = 0.0f;
    //        bIsRest = false;
    //        GetCharacterMovement()->MaxWalkSpeed = 100.0f;
    //    },
    //    RestTime,
    //    false
    //);
}

