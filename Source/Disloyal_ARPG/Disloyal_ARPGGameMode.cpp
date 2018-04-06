// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Disloyal_ARPGGameMode.h"
#include "Disloyal_ARPGPlayerController.h"
#include "Disloyal_ARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADisloyal_ARPGGameMode::ADisloyal_ARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADisloyal_ARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}