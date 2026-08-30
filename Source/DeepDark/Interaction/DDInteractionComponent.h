// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DDInteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom))
class DEEPDARK_API UDDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDDInteractionComponent();
	void TryInteract();

private:
	bool TraceForInteractable(FHitResult& OutHit) const;
	
	UPROPERTY(EditAnywhere, Category="Interaction", meta=(ClampMin="0.0", ClampMax="500.0"))
	float InteractionDistance = 200.f;

	UPROPERTY(EditAnywhere, Category="Interaction", meta=(ClampMin="0.0", ClampMax="20.0"))
	float InteractionRadius = 5.f;
	
};
