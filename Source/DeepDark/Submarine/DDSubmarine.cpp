#include "DDSubmarine.h"

#include "Components/BatteryComponent.h"
#include "Components/PowerComponent.h"

ADDSubmarine::ADDSubmarine()
{
	PrimaryActorTick.bCanEverTick = true;

	SubmarineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubmarineMesh"));
	RootComponent = SubmarineMesh;
	SubmarineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics	);
	
	BatteryComponent = CreateDefaultSubobject<UBatteryComponent>(TEXT("BatteryComponent"));
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
}

void ADDSubmarine::BeginPlay()
{
	Super::BeginPlay();
}

void ADDSubmarine::Tick(float DeltaTime)
{
	const float CurrentLoad = PowerComponent->GetCurrentLoad();

	// E = P × t
	// E - потреблённая энергия (кВт⋅ч)
	// P - текущая мощность (кВт)
	// t - время работы
	const float EnergyConsumed = (CurrentLoad * DeltaTime) / 3600.0f;

	BatteryComponent->ConsumeEnergy(EnergyConsumed);
}


