// Fill out your copyright notice in the Description page of Project Settings.


#include "DDGameMode.h"

ADDGameMode::ADDGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_MainCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}