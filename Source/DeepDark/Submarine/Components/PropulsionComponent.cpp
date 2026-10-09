#include "PropulsionComponent.h"

UPropulsionComponent::UPropulsionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPropulsionComponent::BeginPlay()
{
	Super::BeginPlay();
}

