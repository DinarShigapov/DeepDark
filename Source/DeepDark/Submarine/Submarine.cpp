#include "Submarine.h"
#include "Components/PowerComponent.h"
#include "Components/PropulsionComponent.h"
#include "DeepDark/Items/Battery.h"

ASubmarine::ASubmarine()
{
	PrimaryActorTick.bCanEverTick = true;

	SubmarineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubmarineMesh"));
	RootComponent = SubmarineMesh;
	SubmarineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics	);
	
	Battery = CreateDefaultSubobject<ABattery>(TEXT("Battery"));
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
	PropulsionComponent = CreateDefaultSubobject<UPropulsionComponent>(TEXT("PropulsionComponent"));
}

void ASubmarine::BeginPlay()
{
	Super::BeginPlay();
	
	PowerComponent->RegisterConsumer(PropulsionComponent);
		
}


void ASubmarine::Tick(float DeltaTime)
{

}



