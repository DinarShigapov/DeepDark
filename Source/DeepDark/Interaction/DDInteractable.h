// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DDInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
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