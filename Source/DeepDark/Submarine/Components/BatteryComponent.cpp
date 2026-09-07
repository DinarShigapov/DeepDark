#include "BatteryComponent.h"


UBatteryComponent::UBatteryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBatteryComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = MaxEnergy;
}

bool UBatteryComponent::ConsumeEnergy(float Amount)
{
	CurrentEnergy = FMath::Clamp(CurrentEnergy - Amount, 0.f, MaxEnergy);
	return true;
}
