#include "BatterySlotComponent.h"
#include "PowerComponent.h"
#include "DeepDark/MainCharacter.h"

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
	if (!IsValid(PowerComponent))
	{
		return;
	}
	
	AMainCharacter* Character = Cast<AMainCharacter>(Interactor);
	
	if (!IsValid(Character))
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%d"), SlotIndex);
	
	if (PowerComponent->HasBatteryAt(SlotIndex))
	{
		
		//PowerComponent->AddBattery(Character, SlotIndex);
		UE_LOG(LogTemp, Warning, TEXT("БАТАРЕЙКА"));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("АНЛАК"));

}
