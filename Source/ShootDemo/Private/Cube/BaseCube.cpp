// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/UnrealNetwork.h"

#include "Cube/BaseCube.h"
#include "Components/BoxComponent.h"
#include "ShootPlayerState.h"
#include "UMG/ShooterHUD.h"
#include "UMG/ShooterUserWidget.h"

// Sets default values
ABaseCube::ABaseCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeCollisonComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube Box"));
	SetRootComponent(CubeCollisonComponent);

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube static mesh"));
	CubeMesh->SetupAttachment(RootComponent);

	bReplicates = true;
	UE_LOG(LogTemp, Warning, TEXT("cube begin : init "));

}

// Called when the game starts or when spawned
void ABaseCube::BeginPlay()
{
	Super::BeginPlay();
	
	//if (HasAuthority())
	//{
	//	Score = 500;
	//}
}

void ABaseCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCube, Score);
	DOREPLIFETIME(ABaseCube, HitScale);
	DOREPLIFETIME(ABaseCube, HitCount);
	DOREPLIFETIME(ABaseCube, CubeMesh);
}

void ABaseCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (HasAuthority())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Server Score : %d"), Score);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Client Score : %d"), Score);
	//}
}

void ABaseCube::GetBuff(int importantBuff)
{
	Score *= importantBuff;
	CubeMesh->SetMaterial(0, CubeMesh->GetMaterial(1));
}



void ABaseCube::OnHitByProjectile(AController* InstigatingController)
{
	HitCount = FMath::Clamp(HitCount + 1, 0, 2);
	// player 
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//if (APlayerController* PC = Cast<APlayerController>(InstigatingController))
	if(PlayerController)
	{
		if (AShootPlayerState* PS = Cast<AShootPlayerState>(PlayerController->PlayerState))
		{

			//FString msg = FString::Printf(TEXT("cube name :")) + this->GetName() + FString::Printf(TEXT("cube score %d : %d"), score);
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, msg);

			PS->AddScore(Score);

			TObjectPtr<AShooterHUD> m_HUD = Cast<AShooterHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (m_HUD)
			{
				TObjectPtr<UShooterUserWidget> m_UserWidget = Cast<UShooterUserWidget>(m_HUD->WidgetInstance);
				if (m_UserWidget)
				{
					m_UserWidget->UpdatePlayerScore(PS->GetPlayerScore());
				}
			}
		}
	}


	if (HitCount == 1) 
	{
		CubeMesh->SetWorldScale3D(GetActorScale3D() * HitScale);
	}
	if (HitCount == 2)
	{
		Destroy();
	}

}

