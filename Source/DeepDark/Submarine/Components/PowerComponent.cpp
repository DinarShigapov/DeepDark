#include "PowerComponent.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


float UPowerComponent::GetCurrentLoad() const
{
	float CurrentLoad = 0.0f;

	for (const FPowerConsumer& Consumer : Consumers)
	{
		if (Consumer.bEnabled)
		{
			CurrentLoad += Consumer.PowerRequired;
		}
	}

	return CurrentLoad;
}

float UPowerComponent::GetLoadPercent() const
{
	if (MaxPower <= 0.0f)
	{
		return 0.0f;
	}

	return (GetCurrentLoad() / MaxPower) * 100.0f;
}

bool UPowerComponent::TryEnableConsumer(FName ConsumerName) const
{
	const FPowerConsumer* Consumer = FindConsumer(ConsumerName);

	if (!Consumer)
	{
		return false;
	}
	
	if (Consumer->bEnabled)
	{
		return true;
	}

	const float NewLoad = GetCurrentLoad() + Consumer->PowerRequired;

	return NewLoad <= MaxPower;
}

bool UPowerComponent::EnableConsumer(FName ConsumerName)
{
	FPowerConsumer* Consumer = FindConsumer(ConsumerName);

	if (!Consumer)
	{
		return false;
	}
	
	if (Consumer->bEnabled)
	{
		return true;
	}

	if (!TryEnableConsumer(ConsumerName))
	{
		UE_LOG(LogTemp,	Warning,TEXT("Cannot enable %s: power overload!"),	*ConsumerName.ToString());

		return false;
	}

	Consumer->bEnabled = true;

	OnPowerStateChanged.Broadcast(ConsumerName);

	return true;
}

bool UPowerComponent::DisableConsumer(FName ConsumerName)
{
	FPowerConsumer* Consumer = FindConsumer(ConsumerName);

	if (!Consumer)
	{
		return false;
	}

	if (!Consumer->bEnabled)
	{
		return true;
	}
	
	Consumer->bEnabled = false;
	
	OnPowerStateChanged.Broadcast(ConsumerName);

	return true;
}

bool UPowerComponent::IsConsumerEnabled(FName ConsumerName) const
{
	const FPowerConsumer* Consumer = FindConsumer(ConsumerName);

	if (!Consumer)
	{
		return false;
	}

	return Consumer->bEnabled;
}

// Возвращает указатель на найденный Consumer.
// Через возвращаемый указатель Consumer можно изменять.
FPowerConsumer* UPowerComponent::FindConsumer(FName ConsumerName)
{
	for (FPowerConsumer& Consumer : Consumers)
	{
		if (Consumer.Name == ConsumerName)
		{
			return &Consumer;
		}
	}

	return nullptr;
}

// Возвращает указатель на найденный Consumer только для чтения.
const FPowerConsumer* UPowerComponent::FindConsumer(FName ConsumerName) const
{
	for (const FPowerConsumer& Consumer : Consumers)
	{
		if (Consumer.Name == ConsumerName)
		{
			return &Consumer;
		}
	}

	return nullptr;
}
