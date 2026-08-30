// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DDGameFlowManager.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDDGameFlowState : uint8
{
	MainMenu,
	Loading,
	Gameplay,
	Paused,
	DemoEnd
};


UCLASS()
class DEEPDARK_API UDDGameFlowManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void OpenMainMenu();

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void EndDemo();

	UFUNCTION(BlueprintPure)
	EDDGameFlowState GetCurrentState() const;

private:

	UPROPERTY()
	EDDGameFlowState CurrentState =	EDDGameFlowState::MainMenu;
	
};
