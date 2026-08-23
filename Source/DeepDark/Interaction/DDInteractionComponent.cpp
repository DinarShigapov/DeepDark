// Fill out your copyright notice in the Description page of Project Settings.


#include "DDInteractable.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "DDInteractionComponent.h"


// Sets default values for this component's properties
UDDInteractionComponent::UDDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDDInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Пытается взаимодействовать с объектом, на который смотрит Character
// Сначала, выполняется трассировка от камеры и определяется объект под прицелом.
// Если объект найден и реализует интерфейс UDDInteractable, вызывается его метод Interact() с владельцем компонента в качестве источника взаимодействия.
void UDDInteractionComponent::TryInteract()
{
	FHitResult Hit;

	if (!TraceForInteractable(Hit))
	{
		return;
	}

	AActor* HitActor = Hit.GetActor();

	if (!HitActor)
	{
		return;
	}

	if (HitActor->GetClass()->ImplementsInterface(UDDInteractable::StaticClass()))
	{
		IDDInteractable* Interactable =	Cast<IDDInteractable>(HitActor);

		if (Interactable)
		{
			Interactable->Interact(GetOwner());
		}
	}
}

// Создает луч от камеры игрока и определяет объект, на который направлен взгляд игрока в пределах InteractionDistance.
bool UDDInteractionComponent::TraceForInteractable(FHitResult& OutHit) const
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

	// Проверка лучом, куда смотрит игрок
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.0f, 0, 2.0f);
	
	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End,ECC_Visibility, QueryParams);
}

void UDDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
