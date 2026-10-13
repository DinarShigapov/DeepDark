#include "PickupItem.h"

#include "DeepDark/MainCharacter.h"


APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetGenerateOverlapEvents(false);

	SavedCollisionEnabled = Mesh->GetCollisionEnabled();
}

void APickupItem::Interact(AActor* Interactor)
{
}

void APickupItem::SetHeldMode(bool bHeld)
{
	if (!Mesh)
	{
		return;
	}

	if (bHeld)
	{
		SavedCollisionEnabled = Mesh->GetCollisionEnabled();
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetGenerateOverlapEvents(false);
	}
	else
	{
		Mesh->SetCollisionEnabled(SavedCollisionEnabled);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		Mesh->SetGenerateOverlapEvents(false);
	}
}

bool APickupItem::TryPickup(AMainCharacter* Character)
{
	if (!IsValid(Character))
	{
		return false;
	}
	
	return true;
}
