#include "PowerComponent.h"
#include "DeepDark/Items/Battery.h"
#include "DeepDark/Submarine/Interfaces/PowerConsumer.h"

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

bool UPowerComponent::AddBattery(ABattery* Battery)
{
	if (!Battery)
	{
		return false;
	}
	
	if (Batteries.Contains(Battery))
	{
		return false;
	}
	
	Batteries.Add(Battery);
	
	return true;
}

bool UPowerComponent::RemoveBattery(ABattery* Battery)
{
	if (!Battery)
	{
		return false;
	}
	
	const int32 Removed = Batteries.Remove(Battery);
	
	return Removed > 0;
}

bool UPowerComponent::RegisterConsumer(UActorComponent* Consumer)
{
	if (!Consumer)
	{
		return false;
	}

	if (!Consumer->GetClass()->ImplementsInterface(UPowerConsumer::StaticClass()))
	{
		return false;
	}
	
	if (Consumers.Contains(Consumer))
	{
		return false;
	}
	
	Consumers.Add(Consumer);
	
	RecalculateLoad();
	
	return true;
}

bool UPowerComponent::UnRegisterConsumer(UActorComponent* Consumer)
{
	if (!Consumer)
	{
		return false;
	}
	
	const int32 Removed = Consumers.Remove(Consumer);
	
	if (Removed == 0)
	{
		return false;
	}
	
	RecalculateLoad();
	
	return true;
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
	const float EnergyReceived = RequestEnergy(EnergyToConsume);
	
	
	if (EnergyReceived < EnergyToConsume - KINDA_SMALL_NUMBER)
	{
		// Всё гг, братишка, вырубай 
	}
}


float UPowerComponent::RequestEnergy(float Amount)
{
	if (Amount <= 0.0f)
	{
		return 0.0f;
	}

	TArray<ABattery*> ActiveBatteries;
	
	for (ABattery* Battery : Batteries)
	{
		if (!IsValid(Battery))
		{
			continue;
		}
		
		if (Battery->IsEmpty())
		{
			continue;
		}
		
		ActiveBatteries.Add(Battery);
	}
	
	float Remaining = Amount;

	while (Remaining > KINDA_SMALL_NUMBER && !ActiveBatteries.IsEmpty())
	{
		const float Share = Remaining / ActiveBatteries.Num();

		float ConsumedThisRound = 0.0f;

		for (ABattery* Battery : ActiveBatteries)
		{
			if (!IsValid(Battery))
			{
				continue;
			}

			if (Battery->IsEmpty())
			{
				continue;
			}
			
			const float EnergyToConsume = FMath::Min(Share, Battery->GetAvailableEnergy());
			const float Consumed = Battery->ConsumeEnergy(EnergyToConsume);

			ConsumedThisRound += Consumed;
		}

		Remaining -= ConsumedThisRound;
		
		ActiveBatteries.RemoveAll([](ABattery* Battery)
			{
					return !IsValid(Battery) ||	Battery->IsEmpty();
			}
		);
		
		if (ConsumedThisRound <= KINDA_SMALL_NUMBER)
		{
			break;
		}
	}
	
	return Amount - Remaining;
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
