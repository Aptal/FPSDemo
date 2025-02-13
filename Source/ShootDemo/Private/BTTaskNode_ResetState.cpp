// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ResetState.h"

UBTTaskNode_ResetState::UBTTaskNode_ResetState()
{
	bCreateNodeInstance = true;
	NodeName = "Reset State";
}

EBTNodeResult::Type UBTTaskNode_ResetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemorry)
{
	return EBTNodeResult::Type();
}
