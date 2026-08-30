// Fill out your copyright notice in the Description page of Project Settings.


#include "DDGameFlowManager.h"

void UDDGameFlowManager::StartGame()
{
	CurrentState = EDDGameFlowState::Gameplay;
}

void UDDGameFlowManager::OpenMainMenu()
{
	CurrentState = EDDGameFlowState::MainMenu;
}

void UDDGameFlowManager::PauseGame()
{
	CurrentState = EDDGameFlowState::Paused;
}

void UDDGameFlowManager::ResumeGame()
{
	CurrentState = EDDGameFlowState::Gameplay;
}

void UDDGameFlowManager::EndDemo()
{
	CurrentState = EDDGameFlowState::DemoEnd;
}

EDDGameFlowState UDDGameFlowManager::GetCurrentState() const
{
	return CurrentState;
}