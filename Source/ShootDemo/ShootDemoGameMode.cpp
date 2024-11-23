// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootDemoGameMode.h"
#include "ShootDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootDemoGameMode::AShootDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
