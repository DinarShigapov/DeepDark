#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerConsumer.generated.h"

UINTERFACE(MinimalAPI)
class UPowerConsumer : public UInterface
{
	GENERATED_BODY()
};

class DEEPDARK_API IPowerConsumer
{
	GENERATED_BODY()
	
	public:
	
	virtual float GetCurrentPowerConsumption() const = 0;
	virtual float GetMaxPowerConsumption() const = 0;
};
