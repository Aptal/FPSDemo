// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NonPlayerCharacterAIController.generated.h"

class UBehaviorTreeComponent;
class ANonPlayerCharacter;

UCLASS()
class SHOOTDEMO_API ANonPlayerCharacterAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTreeComponent* BTComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	ANonPlayerCharacter* NPC;

public:
	ANonPlayerCharacterAIController();

	virtual void Tick(float DeltaTime) override;

	void Rest();

protected:
	virtual void BeginPlay() override;

};
