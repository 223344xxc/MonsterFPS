// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

int AShotGun::OnFire(UCameraComponent* cameraComponent) {
	if (curAmmoCount <= 0) {
		Reload();
		return 0;
	}

	if (isReload)
		CancleReload();

	int returnValue = 1;

	for (int i = 0; i < oneShotBulletCount; i++)
		if (RayCasting(cameraComponent)) {

			//SetUpNextShot();
			returnValue = 2;
		}
	
	SetUpNextShot();
	return returnValue;
}