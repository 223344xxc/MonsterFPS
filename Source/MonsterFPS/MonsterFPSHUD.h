// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MonsterFPSHUD.generated.h"

UCLASS()
class AMonsterFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMonsterFPSHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

