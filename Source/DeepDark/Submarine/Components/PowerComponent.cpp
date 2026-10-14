#include "PowerComponent.h"
#include "DeepDark/Items/Battery.h"
#include "DeepDark/Submarine/Interfaces/PowerConsumer.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	BatterySlots.SetNum(SlotCount);
}

void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(PowerTimerHandle, this, &UPowerComponent::UpdatePower, PowerUpdateInterval, true);
	}
}

bool UPowerComponent::AddBattery(ABattery* Battery, int32 SlotIndex)
{
	if (!IsValid(Battery))
	{
		return false;
	}

	if (!BatterySlots.IsValidIndex(SlotIndex))
	{
		return false;
	}
	
	if (IsValid(BatterySlots[SlotIndex].Get()))
	{
		return false;
	}
	
	BatterySlots[SlotIndex] = Battery;
	return true;
}

ABattery* UPowerComponent::RemoveBattery(int32 SlotIndex)
{
	if (!BatterySlots.IsValidIndex(SlotIndex))
	{
		return nullptr;
	}
	
	ABattery* Battery = BatterySlots[SlotIndex].Get();
	
	if (!IsValid(Battery))
	{
		return nullptr;
	}
	
	BatterySlots[SlotIndex] = nullptr;
	return Battery;
}

bool UPowerComponent::RegisterConsumer(UActorComponent* Consumer)
{
	if (!IsValid(Consumer))
	{
		return false;
	}
	
	if (Consumers.Contains(Consumer))
	{
		return false;
	}
	
	IPowerConsumer* ConsumerInterface = Cast<IPowerConsumer>(Consumer);

	if (!ConsumerInterface)
	{
		return false;
	}

	const int32 InsertIndex = Consumers.IndexOfByPredicate(
		[ConsumerInterface](const TObjectPtr<UActorComponent>& Existing)
		{
			const IPowerConsumer* ExistingInterface = Cast<IPowerConsumer>(Existing.Get());

			return ExistingInterface &&
				ConsumerInterface->GetPowerPriority() <
				ExistingInterface->GetPowerPriority();
		});

	if (InsertIndex == INDEX_NONE)
	{
		Consumers.Add(Consumer);
	}
	else
	{
		Consumers.Insert(Consumer, InsertIndex);
	}

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

bool UPowerComponent::HasBatteryAt(int32 SlotIndex) const
{
	if (SlotIndex < 0 || SlotIndex > SlotCount - 1)
	{
		return false;
	}
	
	if (!BatterySlots.IsValidIndex(SlotIndex))
	{
		return false;
	}

	ABattery* Battery = BatterySlots[SlotIndex];
	return Battery != nullptr;
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

		if (!PowerConsumer->IsPowered())
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
		RecalculatePower();
	}
}

void UPowerComponent::RecalculatePower()
{
	
	for (int32 i = Consumers.Num() - 1; i >= 0; --i)
	{
		UActorComponent* Consumer = Consumers[i];
		
		if (!IsValid(Consumer))
		{
			continue;
		}

		IPowerConsumer* PowerConsumer = Cast<IPowerConsumer>(Consumer);

		if (!PowerConsumer)
		{
			continue;
		}
		
		if (!PowerConsumer->IsPowered())
		{
			continue;
		}
		
		PowerConsumer->SetPowered(false);
		break;
	}

	RecalculateLoad();
}


float UPowerComponent::RequestEnergy(float Amount)
{
	if (Amount <= 0.0f)
	{
		return 0.0f;
	}

	TArray<ABattery*> ActiveBatteries;
	
	for (ABattery* Battery : BatterySlots)
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

// Возвращает множитель перегрузки системы питания.
float UPowerComponent::GetOverloadMultiplier() const
{
	if (CurrentLoad <= MaxPower)
	{
		return 1.0f;
	}
	
	const float OverloadRatio = CurrentLoad / MaxPower;
	
	return OverloadRatio;
}
