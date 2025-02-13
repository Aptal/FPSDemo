// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObject.h"
#include "PatrolPath.generated.h"

class USplineComponent;

UCLASS()
class SHOOTDEMO_API APatrolPath : public ASmartObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComp;

	TArray<FVector> WayPoints;
	
protected:
	virtual void BeginPlay() override;

public:
	APatrolPath();

	TArray<FVector>& GetWayPoints() { return WayPoints; }
};
