// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NonPlayerCharacter.generated.h"

class ASmartObject;

UCLASS()
class SHOOTDEMO_API ANonPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	ASmartObject* SmartObject;

	UPROPERTY(EditAnywhere, Category = "AI")
	float Fatigue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool bIsRest = false;

	FTimerHandle RestTimerHandle;

public:
	// Sets default values for this character's properties
	ANonPlayerCharacter();

	static const float FATIGUE_THRESHOLD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:
	FORCEINLINE ASmartObject* GetSmartObject() const { return SmartObject; }

    UFUNCTION(BlueprintCallable)
	float GetFatigue() const { return Fatigue; }

	UFUNCTION(BlueprintCallable)
	void SetRest() { bIsRest = true; }

	UFUNCTION(BlueprintCallable)
	bool IsResting() const { return bIsRest; }

    // 增加疲劳度
    UFUNCTION(BlueprintCallable)
	void IncreaseFatigue(float amount) { Fatigue += amount; }

    // 重置疲劳度
    UFUNCTION(BlueprintCallable)
	void ResetFatigue();

	UFUNCTION(BlueprintCallable)
	void StartResting();
};
