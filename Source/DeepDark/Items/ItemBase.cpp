#include "ItemBase.h"

#include "DeepDark/MainCharacter.h"


AItemBase::AItemBase()
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

void AItemBase::Interact(AActor* Interactor)
{
}

bool AItemBase::TryPickup(AMainCharacter* Character)
{
	if (!IsValid(Character))
	{
		return false;
	}
	
	return true;
}
