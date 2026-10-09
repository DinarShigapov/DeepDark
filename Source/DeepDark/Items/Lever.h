#pragma once

#include "CoreMinimal.h"
#include "DeepDark/Interaction/Interactable.h"
#include "DeepDark/Submarine/Interfaces/PowerConsumer.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class DEEPDARK_API ALever : public AActor, public IInteractable, public IPowerConsumer
{
	
private:
	GENERATED_BODY()

public:	
	ALever();
	
	virtual float GetCurrentPowerConsumption() const override;
	virtual float GetMaxPowerConsumption() const override;
	virtual void SetPowered(bool bPowered) override;
	virtual void OnPowerStatusChanged(bool bPowered) override;
	virtual bool IsPowered() const override;
	virtual EPriority GetPowerPriority() const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void Interact(AActor* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
};
