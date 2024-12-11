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
	int Score = 2;

	UPROPERTY(EditAnyWhere, Replicated, category = "Cube Info")
	float HitScale = 0.5;

	UPROPERTY(BlueprintReadOnly, Replicated, category = "Cube Info")
	int HitCount = 0;

	UPROPERTY(EditAnyWhere, Category = "CubeMesh")
	TObjectPtr <UBoxComponent> CubeCollisonComponent;

	UPROPERTY(EditAnyWhere, Replicated, Category = "CubeMesh")
	TObjectPtr<UStaticMeshComponent> CubeMesh;

};
