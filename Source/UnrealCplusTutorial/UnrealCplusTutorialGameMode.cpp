// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCplusTutorialGameMode.h"
#include "UnrealCplusTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealCplusTutorialGameMode::AUnrealCplusTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
