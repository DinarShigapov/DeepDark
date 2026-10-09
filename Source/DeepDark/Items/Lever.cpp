#include "Lever.h"

float ALever::GetCurrentPowerConsumption() const
{
	return 0;
}

float ALever::GetMaxPowerConsumption() const
{
	return 0;
}

void ALever::SetPowered(bool bPowered)
{
}

void ALever::OnPowerStatusChanged(bool bPowered)
{
}

bool ALever::IsPowered() const
{
	return true;
}

EPriority ALever::GetPowerPriority() const
{
	return EPriority::Low;
}

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetGenerateOverlapEvents(false);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();
}

void ALever::Interact(AActor* Interactor)
{
	if (!Interactor)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("!!! LEVER !!!"));
}
