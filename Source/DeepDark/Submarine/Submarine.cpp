#include "Submarine.h"

#include "Components/BatteryComponent.h"
#include "Components/PowerComponent.h"

ASubmarine::ASubmarine()
{
	PrimaryActorTick.bCanEverTick = true;

	SubmarineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubmarineMesh"));
	RootComponent = SubmarineMesh;
	SubmarineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics	);
	
	BatteryComponent = CreateDefaultSubobject<UBatteryComponent>(TEXT("BatteryComponent"));
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
}

void ASubmarine::BeginPlay()
{
	Super::BeginPlay();
}

void ASubmarine::Tick(float DeltaTime)
{

}


