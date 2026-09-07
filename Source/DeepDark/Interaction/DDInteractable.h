#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DDInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UDDInteractable : public UInterface
{
    GENERATED_BODY()
};

class IDDInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact(AActor* Interactor) = 0;
};