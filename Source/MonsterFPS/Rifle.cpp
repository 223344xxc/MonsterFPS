// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HpComponent.h"


int ARifle::OnFire(UCameraComponent* cameraComponent) 
{
	if (curAmmoCount <= 0) {
		Reload();
		return 0;
	}

	if (isReload)
		CancleReload();

	if (RayCasting(cameraComponent)) {

		SetUpNextShot();
		return 2;
	}
	SetUpNextShot();
	return 1;
}