#include "InteractionComponent.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Пытается взаимодействовать с объектом, на который смотрит Character
// Сначала, выполняется трассировка от камеры и определяется объект под прицелом.
// Если объект найден и реализует интерфейс UInteractable, вызывается его метод Interact() с владельцем компонента в качестве источника взаимодействия.
void UInteractionComponent::TryInteract()
{
	FHitResult Hit;

	if (!TraceForInteractable(Hit))
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction: nothing hit"));
		return;
	}

	UPrimitiveComponent* HitComponent = Hit.GetComponent();
	AActor* HitActor = Hit.GetActor();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Interaction hit: Actor=%s Component=%s"),
		*GetNameSafe(HitActor),
		*GetNameSafe(HitComponent)
	);

	if (HitComponent)
	{
		if (IInteractable* Interactable = Cast<IInteractable>(HitComponent))
		{
			Interactable->Interact(GetOwner());
			return;
		}
	}

	if (HitActor)
	{
		if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
		{
			Interactable->Interact(GetOwner());
		}
	}
}

// Создает луч от камеры игрока и определяет объект, на который направлен взгляд игрока в пределах InteractionDistance.
bool UInteractionComponent::TraceForInteractable(FHitResult& OutHit) const
{
	AActor* Owner = GetOwner();

	if (!Owner)
	{
		return false;
	}

	UCameraComponent* Camera =	Owner->FindComponentByClass<UCameraComponent>();

	if (!Camera)
	{
		return false;
	}

	const FVector Start = Camera->GetComponentLocation();
	const FVector End =	Start +	Camera->GetForwardVector() * InteractionDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(InteractionRadius);

	UWorld* World = GetWorld();
	
	if (!World)
	{
		return false;
	}
	
	DrawDebugLine(World, Start, End, FColor::Red, false, 0.0f, 0, 2.0f);
	
	return World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, ECC_Visibility, CollisionShape, QueryParams);
}
