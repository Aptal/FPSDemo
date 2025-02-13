// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTaskNode::UMyBTTaskNode()
{
	bCreateNodeInstance = true;
	NodeName = "Set Move To Location";
}

EBTNodeResult::Type UMyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemorry)
{
	const APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	/*FNavLocation ResultLocation;
	if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), CheckRadius, ResultLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToLocation", ResultLocation.Location);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Set Black %.1f %.1f %.1f"), ResultLocation.Location.X, ResultLocation.Location.Y, ResultLocation.Location.Z));

		return EBTNodeResult::Succeeded;
	}*/

	if (RestLocations.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, RestLocations.Num() - 1);
		
		FVector RandomLocation = RestLocations[RandomIndex];
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToLocation", RandomLocation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

