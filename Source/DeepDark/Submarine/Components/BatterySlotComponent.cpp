// Fill out your copyright notice in the Description page of Project Settings.


#include "BatterySlotComponent.h"

void UBatterySlotComponent::BeginPlay()
{
 Super::BeginPlay();
}


UBatterySlotComponent::UBatterySlotComponent()
{
	bHiddenInGame = false;
}

void UBatterySlotComponent::Interact(AActor* Interactor)
{

	UE_LOG(LogTemp, Warning, TEXT("%d"), SlotIndex);
}
