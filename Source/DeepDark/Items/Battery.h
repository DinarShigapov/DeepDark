#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Battery.generated.h"


UCLASS()
class DEEPDARK_API ABattery : public AItemBase
{
	GENERATED_BODY()

public:	
	ABattery();
	
	float GetMaxEnergy() const
	{
		return Capacity;
	}
	
	float GetAvailableEnergy() const
	{
		return CurrentEnergy;
	}
	
	float GetChargePercent() const;
	bool IsEmpty() const;
	
	// Вычитает из запаса батареи запрашиваемое количество энергии.
	// Если запрашиваемое количество превышает текущий запас, потребляет только имеющееся.
	// Возвращает фактически потреблённое количество энергии.
	float ConsumeEnergy(float Amount);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(ClampMin="50.0", ClampMax="200.0"))
	float Capacity = 100.0f;
	
	UPROPERTY(VisibleAnywhere)
	float CurrentEnergy = 0.0f;	
};
