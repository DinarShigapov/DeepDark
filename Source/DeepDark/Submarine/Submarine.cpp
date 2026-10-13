#include "Submarine.h"

#include "Components/BatterySlotComponent.h"
#include "Components/PowerComponent.h"
#include "Components/PropulsionComponent.h"
#include "DeepDark/Items/Battery.h"

ASubmarine::ASubmarine()
{
	PrimaryActorTick.bCanEverTick = true;

	SubmarineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubmarineMesh"));
	RootComponent = SubmarineMesh;
	SubmarineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics	);
	
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
	PropulsionComponent = CreateDefaultSubobject<UPropulsionComponent>(TEXT("PropulsionComponent"));

	for (int32 Index = 0; Index < 4; ++Index)
	{
		const FName SlotName = *FString::Format(TEXT("BatterySlot_{0}"), { Index });
		
		UBatterySlotComponent* Slot = CreateDefaultSubobject<UBatterySlotComponent>(SlotName);
		Slot->SlotIndex = Index;
		Slot->SetupAttachment(RootComponent);
		Slot->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));


		
		BatterySlots.Add(Slot);
	}
}

void ASubmarine::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(PowerComponent))
	{
		return;
	}
	
	PowerComponent->RegisterConsumer(PropulsionComponent);
	
	for (UBatterySlotComponent* Slot : BatterySlots)
	{
		
		Slot->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Slot->SetCollisionObjectType(ECC_WorldDynamic);
		Slot->SetCollisionResponseToAllChannels(ECR_Block);
		
		DrawDebugBox(
			GetWorld(),Slot->GetComponentLocation(), Slot->GetScaledBoxExtent(),Slot->GetComponentQuat(), FColor::Green,false, 
			99.0f,
			 0,
			 2.0f);
		Slot->PowerComponent = PowerComponent;
	}
	
	
}


