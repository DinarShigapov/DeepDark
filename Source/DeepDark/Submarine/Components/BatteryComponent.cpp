#include "BatteryComponent.h"

UBatteryComponent::UBatteryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBatteryComponent::SetMaxPower(float NewMaxPower)
{
	if (NewMaxPower < 0)
	{
		MaxPower = 0;
	}
	else if (NewMaxPower > 100)
	{
		MaxPower = 100;
	}
	else
	{
		MaxPower = NewMaxPower;
	}
}

float UBatteryComponent::GetCurrentLoad() const
{
	float CurrentLoad = 0.0f;

	for (const FBatteryConsumer& Consumer : Consumers)
	{
		if (Consumer.bEnabled)
		{
			CurrentLoad += Consumer.PowerRequired;
		}
	}

	return CurrentLoad;
}

float UBatteryComponent::GetLoadPercent() const
{
	if (MaxPower <= 0.0f)
	{
		return 0.0f;
	}

	return (GetCurrentLoad() / MaxPower) * 100.0f;
}

bool UBatteryComponent::TryEnableConsumer(FName ConsumerName) const
{
	const FBatteryConsumer* Consumer = FindConsumer(ConsumerName);

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

bool UBatteryComponent::EnableConsumer(FName ConsumerName)
{
	FBatteryConsumer* Consumer = FindConsumer(ConsumerName);

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
		UE_LOG(LogTemp,	Warning,TEXT("Cannot enable %s: power overload!"),	*ConsumerName.ToString()
		);

		return false;
	}


	Consumer->bEnabled = true;

	OnPowerStateChanged.Broadcast(ConsumerName);

	return true;
}

bool UBatteryComponent::DisableConsumer(FName ConsumerName)
{
	FBatteryConsumer* Consumer = FindConsumer(ConsumerName);

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

bool UBatteryComponent::IsConsumerEnabled(FName ConsumerName) const
{
	const FBatteryConsumer* Consumer = FindConsumer(ConsumerName);

	if (!Consumer)
	{
		return false;
	}

	return Consumer->bEnabled;
}

// Возвращает указатель на найденный Consumer.
// Через возвращаемый указатель Consumer можно изменять.
FBatteryConsumer* UBatteryComponent::FindConsumer(FName ConsumerName)
{
	for (FBatteryConsumer& Consumer : Consumers)
	{
		if (Consumer.Name == ConsumerName)
		{
			return &Consumer;
		}
	}

	return nullptr;
}

// Возвращает указатель на найденный Consumer только для чтения.
const FBatteryConsumer* UBatteryComponent::FindConsumer(FName ConsumerName) const
{
	for (const FBatteryConsumer& Consumer : Consumers)
	{
		if (Consumer.Name == ConsumerName)
		{
			return &Consumer;
		}
	}

	return nullptr;
}
