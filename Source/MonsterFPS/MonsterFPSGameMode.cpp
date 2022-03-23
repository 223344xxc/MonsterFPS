// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterFPSGameMode.h"
#include "MonsterFPSHUD.h"
#include "MonsterFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMonsterFPSGameMode::AMonsterFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnClassFinder(TEXT("/Game/Blueprint/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMonsterFPSHUD::StaticClass();
}
