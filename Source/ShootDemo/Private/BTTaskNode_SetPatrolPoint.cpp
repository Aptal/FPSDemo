// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetPatrolPoint.h"
#include "SmartObject.h"
#include "NonPlayerCharacter.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPath.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_SetPatrolPoint::UBTTaskNode_SetPatrolPoint()
{
	bCreateNodeInstance = true;
	NodeName = "Set Patrol Point";
}

EBTNodeResult::Type UBTTaskNode_SetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemorry)
{
	ANonPlayerCharacter* NPC = Cast<ANonPlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (!NPC)
	{
		return EBTNodeResult::Failed;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Fatigue %.1f"), NPC->GetFatigue()));

	if (NPC->IsResting() == false)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool("IsRest", false);
		}
		NPC->StartResting();
	}

	if (NPC->GetFatigue() >= NPC->FATIGUE_THRESHOLD)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("start Fatigue %.1f"), NPC->GetFatigue()));

		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool("IsRest", true);
		}
		NPC->StartResting();
		return EBTNodeResult::Succeeded;
	}

	ASmartObject* SmartObj = NPC->GetSmartObject();

	if (!SmartObj)
	{
		return EBTNodeResult::Failed;
	}

	APatrolPath* Path = Cast<APatrolPath>(SmartObj);
	if (Path == nullptr || Path->GetWayPoints().Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToLocation", Path->GetWayPoints()[WaypointIndex]);
	float randomFloat = 50.0f; // FMath::FRandRange(10.0f, 20.0f);
	NPC->IncreaseFatigue(randomFloat);
	WaypointIndex = WaypointIndex + 1 >= Path->GetWayPoints().Num() ? 0 : WaypointIndex + 1;

	return EBTNodeResult::Succeeded;
}
