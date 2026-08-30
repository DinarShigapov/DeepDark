// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DDInteractable.generated.h"


// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDDInteractable : public UInterface
{
    GENERATED_BODY()
};

class IDDInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Interact(AActor* Character);
};