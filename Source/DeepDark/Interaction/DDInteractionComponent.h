// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DDInteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPDARK_API UDDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDDInteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	bool TraceForInteractable(FHitResult& OutHit) const;
	
	UPROPERTY(EditAnywhere, Category="Interaction")
	float InteractionDistance = 200.0f;
		
};
