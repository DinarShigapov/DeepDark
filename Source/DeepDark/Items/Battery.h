#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Battery.generated.h"


UCLASS()
class DEEPDARK_API ABattery : public AActor
{
	GENERATED_BODY()

public:	
	ABattery();
	
	float GetMaxEnergy() const
	{
		return Capacity;
	}
	
	float GetChargePercent() const
	{
		return (CurrentEnergy / Capacity) * 100.0f;
	}
	
	float GetAvailableEnergy() const
	{
		return CurrentEnergy;
	}
	
	bool IsEmpty() const;
	float ConsumeEnergy(float Amount);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(ClampMin="50.0", ClampMax="200.0"))
	float Capacity = 100.0f;
	
	UPROPERTY(VisibleAnywhere)
	float CurrentEnergy = 0.0f;	
};
