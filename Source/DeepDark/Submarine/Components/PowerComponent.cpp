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

void UPowerComponent::AddBattery(UBatteryComponent* Battery)
{
	if (!Battery)
	{
		return;
	}
	
	if (Batteries.Contains(Battery))
	{
		return;
	}
	
	Batteries.Add(Battery);
}

void UPowerComponent::RemoveBattery(UBatteryComponent* Battery)
{
	if (!Battery)
	{
		return;
	}
	
	Batteries.Remove(Battery);
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

bool UPowerComponent::CanProvideEnergy(float Amount) const
{
	if (Amount <= 0.0f)
	{
		return false;
	}
	
	float AvailableEnergy = 0.0f;
	
	for (UBatteryComponent* Battery : Batteries)
	{
		if (!Battery)
		{
			continue;
		}
		
		AvailableEnergy += Battery->GetAvailableEnergy();
		
		if (AvailableEnergy >= Amount)
		{
			return true;
		}
	}
	
	return false;
}

bool UPowerComponent::RequestEnergy(float Amount)
{
	if (Amount <= 0.f)
	{
		return false;
	}
	
	if (!CanProvideEnergy(Amount))
	{
		return false;
	}

	float Remaining = Amount;

	for (UBatteryComponent* Battery : Batteries)
	{
		if (!Battery)
		{
			continue;
		}
		
		const float AvailableEnergy = Battery->GetAvailableEnergy();
		
		if (AvailableEnergy <= 0.0f)
		{
			continue;
		}
		
		const float EnergyToConsume = FMath::Min(Remaining, AvailableEnergy);
		
		Battery->ConsumeEnergy(EnergyToConsume);
		
		if (Remaining <= EnergyToConsume)
		{
			return true;
		}
	}
	
	return false;
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
