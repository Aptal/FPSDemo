// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayerCharacterAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NonPlayerCharacter.h"
#include "SmartObject.h"

ANonPlayerCharacterAIController::ANonPlayerCharacterAIController()
{
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree");
}

void ANonPlayerCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (NPC)
	//{
	//	NPC->IncreaseFatigue(DeltaTime * 10.0f); 

	//	if (NPC->GetFatigue() >= ANonPlayerCharacter::FATIGUE_THRESHOLD)
	//	{
	//		Rest();
	//	}
	//}
}

void ANonPlayerCharacterAIController::Rest()
{
	
}

void ANonPlayerCharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}

	NPC = Cast<ANonPlayerCharacter>(GetPawn());

	if (NPC)
	{
		if (ASmartObject* SmartObj = NPC->GetSmartObject())
		{
			if (UBehaviorTree* Subtree = SmartObj->GetSubtree())
			{
				const FGameplayTag SubtreeTag;
				BTComp->SetDynamicSubtree(SubtreeTag, Subtree);
			}
		}
	}
}
