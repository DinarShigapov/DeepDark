#include "BatteryComponent.h"

#include <Programs/UnrealBuildAccelerator/Core/Public/UbaBase.h>


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

bool UBatteryComponent::ConsumeEnergy(float Amount)
{
	if (Amount <= 0.0f)
	{
		return false;
	}
	
	CurrentEnergy = FMath::Min(Amount, CurrentEnergy);
	
	return true;
}
