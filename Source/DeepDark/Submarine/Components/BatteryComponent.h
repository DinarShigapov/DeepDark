#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BatteryComponent.generated.h"


UCLASS()
class DEEPDARK_API UBatteryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBatteryComponent();

	// Возвращает максимальный заряд батареи
	UFUNCTION(BlueprintPure)
	float GetMaxEnergy() const
	{
		return MaxEnergy;
	}
	
	// Возвращает заряда батареи
	UFUNCTION(BlueprintPure)
	float GetCurrentEnergy() const
	{
		return CurrentEnergy;
	}
	
	// Возвращает процент заряда батареи 
	UFUNCTION(BlueprintPure, Category="Battery")
	float GetChargePercent() const
	{
		return (CurrentEnergy / MaxEnergy) * 100.0f;
	}

	// Расходует энергию
	UFUNCTION(BlueprintCallable, Category="Battery")
	bool ConsumeEnergy(float Amount);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(ClampMin="50.0", ClampMax="200.0"))
	float MaxEnergy = 100.0f; // кВт.ч
	
	UPROPERTY(VisibleAnywhere)
	float CurrentEnergy = 0.0f;	
};
