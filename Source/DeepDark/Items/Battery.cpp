#include "Battery.h"

ABattery::ABattery()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABattery::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = Capacity;
}

bool ABattery::IsEmpty() const
{
	if (CurrentEnergy <= KINDA_SMALL_NUMBER)
	{
		return true;
	}
	return false;
}

float ABattery::ConsumeEnergy(float Amount)
{
	if (Amount <= 0.0f)
	{
		return 0.0f;
	}
	
	const float EnergyToConsume = FMath::Min(Amount, CurrentEnergy);
	
	CurrentEnergy -= EnergyToConsume;
	
	return EnergyToConsume;
}
