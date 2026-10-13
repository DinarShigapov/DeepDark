#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DeepDark/Interaction/Interactable.h"
#include "BatterySlotComponent.generated.h"

class UPowerComponent;

UCLASS()
class DEEPDARK_API UBatterySlotComponent : public UBoxComponent, public IInteractable
{
public:
	 UBatterySlotComponent();

private:
	GENERATED_BODY()

public:
	TObjectPtr<UPowerComponent> PowerComponent = nullptr;
	
	virtual void Interact(AActor* Interactor) override;
	
	int32 SlotIndex = 0;
	
};
