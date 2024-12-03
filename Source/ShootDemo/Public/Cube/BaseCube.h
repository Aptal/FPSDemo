// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCube.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTDEMO_API ABaseCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseCube();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	virtual void Tick(float DeltaTime) override;

	void GetBuff(int importantBuff);

	void OnHitByProjectile(AController* InstigatingController);

	UPROPERTY(EditAnyWhere, Replicated, category = "Cube Info")
	int score = 2;

	UPROPERTY(EditAnyWhere, category = "Cube Info")
	float hitScale = 0.5;

	UPROPERTY(BlueprintReadOnly, category = "Cube Info")
	int hitCount = 0;

	UPROPERTY(EditAnyWhere, Category = "CubeMesh")
	TObjectPtr < UBoxComponent> CubeCollisonComponent;

	UPROPERTY(EditAnyWhere, Category = "CubeMesh")
	TObjectPtr<UStaticMeshComponent> CubeMesh;

};
