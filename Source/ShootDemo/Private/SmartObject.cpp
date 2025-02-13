#include "SmartObject.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"


ASmartObject::ASmartObject()
{
 	PrimaryActorTick.bCanEverTick = true;
    
    BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    SetRootComponent(BillboardComp);

    ArrowComp = CreateDefaultSubobject<UArrowComponent>("Arrow");
    ArrowComp->SetupAttachment(BillboardComp);
}


