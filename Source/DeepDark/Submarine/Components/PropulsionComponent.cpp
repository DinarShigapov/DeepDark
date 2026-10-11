#include "PropulsionComponent.h"

float UPropulsionComponent::GetCurrentPowerConsumption() const
{
	return 0;
}

float UPropulsionComponent::GetMaxPowerConsumption() const
{
	return 0;
}

void UPropulsionComponent::SetPowered(bool bPowered)
{
	if (bIsPowered == bPowered)
	{
		return;
	}
	
	bIsPowered = bPowered;
	
	if (!bIsPowered)
	{
		StopPropulsion();
	}
}

bool UPropulsionComponent::IsPowered() const
{
	return bIsPowered;
}

EPriority UPropulsionComponent::GetPowerPriority() const
{
	return EPriority::Low;
}

UPropulsionComponent::UPropulsionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPropulsionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPropulsionComponent::StopPropulsion()
{
	// Оффнись, братух
}

