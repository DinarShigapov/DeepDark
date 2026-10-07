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

bool UBatteryComponent::IsEmpty() const
{
	if (CurrentEnergy <= KINDA_SMALL_NUMBER)
	{
		return true;
	}
	return false;
}

float UBatteryComponent::ConsumeEnergy(float Amount)
{
	if (Amount <= 0.0f)
	{
		return 0.0f;
	}
	
	const float EnergyToConsume = FMath::Min(Amount, CurrentEnergy);
	
	CurrentEnergy -= EnergyToConsume;
	
	return EnergyToConsume;
}
