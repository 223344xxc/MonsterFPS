// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gun.generated.h"

class UCameraComponent;

UCLASS()
class MONSTERFPS_API AGun : public APawn
{
	GENERATED_BODY()

public:
	AGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float shotDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float maxAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float curAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float reloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float gunAngleRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float upCameraAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		FVector attachPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		FVector attachRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		FVector attachScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	bool isReload = false;

	bool canFire = true;
protected:


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	FTimerHandle fireTimerHandle;
	FTimerHandle reloadTimerHandle;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual int OnFire(UCameraComponent* cameraComponent);

	void SetUpNextShot();

	void ReadyFire();

	bool ApplyDamage(FHitResult* hit);

	virtual bool RayCasting(UCameraComponent* cameraComponent);

	virtual void Reload();
	virtual void CancleReload();
	virtual void EndReload();
};
