#include "PropulsionComponent.h"

UPropulsionComponent::UPropulsionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPropulsionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPropulsionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

