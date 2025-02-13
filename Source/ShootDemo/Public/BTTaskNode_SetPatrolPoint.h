// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTDEMO_API UBTTaskNode_SetPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	int32 WaypointIndex;

public:
	UBTTaskNode_SetPatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemorry) override;
	
};
