#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPowerConsumer.generated.h"

UINTERFACE(MinimalAPI)
class UIPowerConsumer : public UInterface
{
	GENERATED_BODY()
};

class DEEPDARK_API IIPowerConsumer
{
	GENERATED_BODY()
	
	public:
	
	virtual float GetCurrentPowerConsumption() const = 0;
	virtual float GetMaxPowerConsumption() const = 0;
};
