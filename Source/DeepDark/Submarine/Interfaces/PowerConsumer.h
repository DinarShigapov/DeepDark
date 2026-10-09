#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerConsumer.generated.h"

UENUM()
enum class EPriority : uint8
{
	High    = 0,  
	Medium  = 1,   
	Low     = 2
};

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
	virtual void SetPowered(bool bPowered) = 0;
	virtual void OnPowerStatusChanged(bool bPowered) = 0;
	virtual bool IsPowered() const = 0;
	virtual EPriority GetPowerPriority() const = 0;
};
