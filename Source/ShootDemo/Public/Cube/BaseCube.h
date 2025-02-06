// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCube.generated.h"

class UBoxComponent;
class AShootDemoPlayerController;

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

	// 服务器上运行，可靠函数
	UFUNCTION(Server, Reliable, WithValidation)
	void OnHitByProjectile(AShootDemoPlayerController* PlayerController);
	virtual bool OnHitByProjectile_Validate(AShootDemoPlayerController* PlayerController);
	virtual void OnHitByProjectile_Implementation(AShootDemoPlayerController* PlayerController);

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
