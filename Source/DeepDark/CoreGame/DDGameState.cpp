// Fill out your copyright notice in the Description page of Project Settings.


#include "DDGameState.h"

EDDGameplayState ADDGameState::GetGameplayState() const
{
	return GameplayState;
}


void ADDGameState::SetGameplayState(
	EDDGameplayState NewState)
{
	GameplayState = NewState;
}