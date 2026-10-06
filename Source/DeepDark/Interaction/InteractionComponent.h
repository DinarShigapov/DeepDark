#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom))
class DEEPDARK_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
	void TryInteract();

private:
	bool TraceForInteractable(FHitResult& OutHit) const;
	
	UPROPERTY(EditAnywhere, Category="Interaction", meta=(ClampMin="0.0", ClampMax="500.0"))
	float InteractionDistance = 200.f;

	UPROPERTY(EditAnywhere, Category="Interaction", meta=(ClampMin="0.0", ClampMax="20.0"))
	float InteractionRadius = 5.f;
	
};
