// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEEPDARK_API ADDPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
};
