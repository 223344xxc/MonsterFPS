// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "DrawDebugHelpers.h"
// Sets default values


APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set our turn rates for input
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRate = 45.f;
	LookUpRate = 45.f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (onTrigger && gun[ctrlGunIndex]->canFire) {
		OnFire();
	}

	if (tryRecoil) {

		AddControllerPitchInput(-recoilNum * DeltaTime);
		AddControllerYawInput((recoilNum * recoilYaw) * DeltaTime);

		acuDeltatime += DeltaTime * 150;
		recoilNum -= (acuDeltatime * acuDeltatime);

		if (recoilNum <= 0.1f) {
			recoilNum = 0;
			acuDeltatime = 0;
			tryRecoil = false;
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::InputTrigger);
	PlayerInputComponent->BindAction("OutTrigger", IE_Released, this, &APlayerCharacter::OutPutTrigger);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);


	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::InputTrigger()
{
	onTrigger = true;
}

void APlayerCharacter::OutPutTrigger() 
{
	onTrigger = false;
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::SetGunIndex(int index)
{
	for (int i = 0; i < gun.Num(); i++) {
		if (gun[i] == nullptr) {
			continue;
		}

		if (index == i) {
			gun[i]->SetActorHiddenInGame(false);
			ctrlGunIndex = index;
		}
		else {
			gun[i]->CancleReload();
			gun[i]->SetActorHiddenInGame(true);
		}
	}
}

void APlayerCharacter::OnFire()
{
	if (gun[ctrlGunIndex] != nullptr) {
		int num = gun[ctrlGunIndex]->OnFire(CameraComponent);

		if (num > 0) {
			UAnimInstance* AnimInstance = ArmMesh->GetAnimInstance();
			if (AnimInstance != nullptr) {
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
			recoilNum = gun[ctrlGunIndex]->upCameraAngle;
			tryRecoil = true;
			recoilYaw = FMath::RandRange(-1.5f, 1.5f);
			if (num == 2)
				onHitDelegate.Broadcast();
		}
	}
}
void APlayerCharacter::Reload() {
	if (gun[ctrlGunIndex] != nullptr) {
		gun[ctrlGunIndex]->Reload();
	}
}