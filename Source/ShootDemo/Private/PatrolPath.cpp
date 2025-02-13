#include "PatrolPath.h"
#include "Components/SplineComponent.h"

APatrolPath::APatrolPath()
{
	SplineComp = CreateDefaultSubobject<USplineComponent>("Path");
	SplineComp->SetupAttachment(GetRootComponent());
}

void APatrolPath::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < SplineComp->GetNumberOfSplinePoints(); ++i)
	{
		WayPoints.AddUnique(SplineComp->GetWorldLocationAtSplinePoint(i));
	}
}
