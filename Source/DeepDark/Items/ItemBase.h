#pragma once

#include "CoreMinimal.h"
#include "DeepDark/MainCharacter.h"
#include "DeepDark/Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UStaticMeshComponent;
class AMainComponent;

UENUM()
enum class EItemLocation : uint8
{
	InWorld,
	Held,
	Installed
};

UCLASS()
class DEEPDARK_API AItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:	
	AItemBase();

	virtual void Interact(AActor* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemLocation ItemLocation = EItemLocation::InWorld;
	
private:
	ECollisionEnabled::Type SavedCollisionEnabled = ECollisionEnabled::QueryOnly;
	bool TryPickup(AMainCharacter* Character);
};
