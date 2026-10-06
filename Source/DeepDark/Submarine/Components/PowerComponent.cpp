#include "PowerComponent.h"
#include "BatteryComponent.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(PowerTimerHandle, this, &UPowerComponent::UpdatePower, PowerUpdateInterval, true);
	}
}

void UPowerComponent::RegisterConsumer(UActorComponent* Consumer)
{
	if (!Consumer)
	{
		return;
	}
	
	if (Consumers.Contains(Consumer))
	{
		return;
	}
	
	Consumers.Add(Consumer);
	
	RecalculateLoad();
}

void UPowerComponent::UnRegisterConsumer(UActorComponent* Consumer)
{
	if (!Consumer)
	{
		return;
	}
	
	Consumers.Remove(Consumer);
	
	RecalculateLoad();
}

void UPowerComponent::NotifyPowerChanged()
{
	RecalculateLoad();
}

void UPowerComponent::RecalculateLoad()
{
	CurrentLoad = 0.f;
	
	for (UActorComponent* Consumer : Consumers)
	{
		if (!Consumer)
		{
			continue;
		}
		IPowerConsumer* PowerConsumer = Cast<IPowerConsumer>(Consumer);
		
		if (!PowerConsumer)
		{
			continue;
		}
		CurrentLoad += PowerConsumer->GetCurrentPowerConsumption();
	}
}

void UPowerComponent::UpdatePower()
{
	const float OverloadMultiplier = GetOverloadMultiplier();
	const float EnergyToConsume = CurrentLoad * PowerUpdateInterval * OverloadMultiplier;
	
	RequestEnergy(EnergyToConsume);
}

float UPowerComponent::GetTotalCurrentEnergy() const
{
	float Total = 0.f;
	for (UBatteryComponent* Battery : Batteries)
	{
		if (Battery)
		{
			Total += Battery->GetCurrentEnergy();
		}
	}
	return Total;
}

bool UPowerComponent::CanProvideEnergy(float Amount) const
{
	return GetTotalCurrentEnergy() >= Amount;
}

bool UPowerComponent::RequestEnergy(float Amount)
{
	if (Amount <= 0.f || !CanProvideEnergy(Amount))
	{
		return false;
	}

	const float PerBattery = Amount / FMath::Max(1, Batteries.Num());

	for (UBatteryComponent* Battery : Batteries)
	{
		if (Battery) Battery->ConsumeEnergy(PerBattery);
	}
	
	return true;
}

float UPowerComponent::GetOverloadMultiplier() const
{
	if (CurrentLoad <= MaxPower)
	{
		return 1.0f;
	}
	
	const float OverloadRatio = CurrentLoad / MaxPower;
	
	return OverloadRatio;
}
