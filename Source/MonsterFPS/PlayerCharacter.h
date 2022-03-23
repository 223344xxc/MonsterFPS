// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHit);

class UCameraComponent;

UCLASS()
class MONSTERFPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float LookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* ArmMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(BlueprintReadWrite)
	TArray<AGun*> gun;
		//AGun* gun;
	UPROPERTY(BlueprintReadWrite)
	int ctrlGunIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool onTrigger;

	//UPROPERTY(BlueprintReadWrite)
	UPROPERTY(BlueprintAssignable)
	FOnHit onHitDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float recoilNum = 0;
	float acuDeltatime;
	int recoilYaw;
	bool tryRecoil = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InputTrigger();
	void OutPutTrigger();

	void OnFire();
	void Reload();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void SetGunIndex(int index);
};
