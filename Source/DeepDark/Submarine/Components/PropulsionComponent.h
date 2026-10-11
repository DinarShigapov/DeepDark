#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeepDark/Submarine/Interfaces/PowerConsumer.h"
#include "PropulsionComponent.generated.h"


UCLASS()
class DEEPDARK_API UPropulsionComponent : public UActorComponent, public IPowerConsumer
{
	GENERATED_BODY()

public:	
	UPropulsionComponent();

	virtual float GetCurrentPowerConsumption() const override;
	virtual float GetMaxPowerConsumption() const override;
	virtual void SetPowered(bool bPowered) override;
	virtual bool IsPowered() const override;
	virtual EPriority GetPowerPriority() const override;
	
protected:
	virtual void BeginPlay() override;
	void StopPropulsion();
	
private:
	bool bIsPowered = false;
};
