#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeepDark/Submarine/Interfaces/PowerConsumer.h"
#include "PowerComponent.generated.h"

class UBatteryComponent;

UCLASS()
class DEEPDARK_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerComponent();
	virtual void BeginPlay() override;
	
	void AddBattery(UBatteryComponent* Battery);
	void RemoveBattery(UBatteryComponent* Battery);
	
	void RegisterConsumer(UActorComponent* Consumer);
	void UnRegisterConsumer(UActorComponent* Consumer);
	
	void NotifyPowerChanged();
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<UBatteryComponent>> Batteries;
	
	UPROPERTY()
	TArray<TObjectPtr<UActorComponent>> Consumers;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="0.01", ClampMax="5.0"))
	float PowerUpdateInterval = 0.1f;

private:
	float GetOverloadMultiplier() const;
	bool CanProvideEnergy(float Amount) const;
	bool RequestEnergy(float Amount);
	void RecalculateLoad();
	void UpdatePower();
	
	const float MaxPower = 100.0f;
	float CurrentLoad = 0.0f; 
	
	FTimerHandle PowerTimerHandle;
	
};
