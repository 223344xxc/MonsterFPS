// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "ShotGun.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERFPS_API AShotGun : public AGun
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float oneShotBulletCount;

	virtual int OnFire(UCameraComponent* cameraComponent) override;
};
