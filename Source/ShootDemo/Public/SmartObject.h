// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartObject.generated.h"

class UArrowComponent;
class UBehaviorTree;
class UBillboardComponent;

UCLASS()
class SHOOTDEMO_API ASmartObject : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UBillboardComponent* BillboardComp;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* Subtree;

public:	
	ASmartObject();
	
	FORCEINLINE UBehaviorTree* GetSubtree() const { return Subtree; }
};
