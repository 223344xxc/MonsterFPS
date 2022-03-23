// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERFPS_API ARifle : public AGun
{
	GENERATED_BODY()
public:
	virtual int OnFire(UCameraComponent* cameraComponent) override;
};
