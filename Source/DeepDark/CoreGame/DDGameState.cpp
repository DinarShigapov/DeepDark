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