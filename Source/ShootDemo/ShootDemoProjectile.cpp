// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootDemoProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Cube/BaseCube.h"
#include "ShootDemoCharacter.h"
#include "ShootDemoPlayerController.h"
#include "Net/UnrealNetwork.h"

AShootDemoProjectile::AShootDemoProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShootDemoProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	//  网络复制
	bReplicates = true;
	SetReplicateMovement(true);
	ProjectileMovement->SetIsReplicated(true);
}

void AShootDemoProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 判断是否击中得分方块
	TObjectPtr<ABaseCube> cube = Cast<ABaseCube>(OtherActor);
	if (cube != nullptr) 
	{
		cube->OnHitByProjectile(Cast<AShootDemoPlayerController>(GetInstigatorController()));
		Destroy();
	}

	TObjectPtr<AShootDemoCharacter> Character = Cast<AShootDemoCharacter>(OtherActor);
	if (Character != nullptr)
	{
		TObjectPtr<AShootDemoPlayerController> PC = Cast<AShootDemoPlayerController>(GetWorld()->GetFirstPlayerController());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("hit pc")));
		if (PC)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("hit pc")));
			PC->ClientChangeCrosshairColor();
			//PC->ChangeCrosshairColorTemporarily();
		}
		Destroy();
	}

	// Only add impulse and destroy projectile if we hit a physics
	// 模板默认的带物理模拟的charmCube
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}

void AShootDemoProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 指定要复制的属性
	DOREPLIFETIME(AShootDemoProjectile, CollisionComp);
	DOREPLIFETIME(AShootDemoProjectile, ProjectileMovement);
}
