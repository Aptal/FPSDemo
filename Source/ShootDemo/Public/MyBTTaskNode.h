// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTDEMO_API UMyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float CheckRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	TArray<FVector> RestLocations;

public:
	UMyBTTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemorry) override;
	
};
