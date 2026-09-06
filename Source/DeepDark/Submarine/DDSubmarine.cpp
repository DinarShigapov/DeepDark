#include "DDSubmarine.h"

#include "Components/BatteryComponent.h"

ADDSubmarine::ADDSubmarine()
{
	PrimaryActorTick.bCanEverTick = false;

	SubmarineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubmarineMesh"));
	RootComponent = SubmarineMesh;
	SubmarineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics	);
	
	BatteryComponent = CreateDefaultSubobject<UBatteryComponent>(TEXT("BatteryComponent"));
}

void ADDSubmarine::BeginPlay()
{
	Super::BeginPlay();
}


