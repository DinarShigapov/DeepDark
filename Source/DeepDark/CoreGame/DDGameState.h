// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DDGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDDGameplayState : uint8
{
	Preparation,
	Launch,
	Descent,
	Event,
	DemoEnd
};

UCLASS()
class DEEPDARK_API ADDGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	EDDGameplayState GetGameplayState() const;
	void SetGameplayState(EDDGameplayState NewState);

private:
	UPROPERTY()
	EDDGameplayState GameplayState = EDDGameplayState::Preparation;
	
};
