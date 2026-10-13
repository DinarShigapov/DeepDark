#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "DeepDark/MainCharacter.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class UStaticMeshComponent;
class AMainComponent;

UCLASS()
class DEEPDARK_API APickupItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:	
	APickupItem();

	virtual void Interact(AActor* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

protected:
	void SetHeldMode(bool bHeld);

private:
	ECollisionEnabled::Type SavedCollisionEnabled = ECollisionEnabled::QueryOnly;
	
	bool TryPickup(AMainCharacter* Character);

};
