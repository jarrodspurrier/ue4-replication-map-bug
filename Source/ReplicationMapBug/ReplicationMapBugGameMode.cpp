// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ReplicationMapBugGameMode.h"
#include "ReplicationMapBugCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReplicationMapBugGameMode::AReplicationMapBugGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
