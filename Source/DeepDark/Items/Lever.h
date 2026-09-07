#pragma once

#include "CoreMinimal.h"
#include "DeepDark/Interaction/DDInteractable.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class DEEPDARK_API ALever : public AActor, public IDDInteractable
{
	GENERATED_BODY()
	
public:	
	ALever();

protected:
	virtual void BeginPlay() override;
	
	virtual void Interact(AActor* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
};
