#include "BatteryComponent.h"


UBatteryComponent::UBatteryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBatteryComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = Capacity;
}

void UBatteryComponent::ConsumeEnergy(float Amount)
{
	if (Amount <= 0)
	{
		return;
	}
	
	CurrentEnergy = FMath::Clamp(CurrentEnergy - Amount, 0.f, Capacity);
}
