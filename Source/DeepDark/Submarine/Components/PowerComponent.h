#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerComponent.generated.h"

class UBatteryComponent;

UCLASS()
class DEEPDARK_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerComponent();
	virtual void BeginPlay() override;
	
	bool AddBattery(UBatteryComponent* Battery);
	bool RemoveBattery(UBatteryComponent* Battery);
	
	bool RegisterConsumer(UActorComponent* Consumer);
	bool UnRegisterConsumer(UActorComponent* Consumer);
	
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
	float RequestEnergy(float Amount);
	void UpdatePower();
	void RecalculateLoad();
	
	const float MaxPower = 100.0f;
	float CurrentLoad = 0.0f; 
	
	FTimerHandle PowerTimerHandle;
};
