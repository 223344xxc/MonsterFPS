// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HpComponent.h"
#include "BulletHole.h"

// Sets default values
AGun::AGun()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	TEnumAsByte<EObjectTypeQuery> PhysicBody = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody);
	ObjectTypes.Add(WorldStatic);
	ObjectTypes.Add(WorldDynamic);
	ObjectTypes.Add(PhysicBody);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int AGun::OnFire(UCameraComponent* cameraComponent)
{
	if (curAmmoCount <= 0) {
		Reload();
		return 0;
	}


	if (isReload)
		CancleReload();

	SetUpNextShot();

	return 1;
}

void AGun::SetUpNextShot()
{
	curAmmoCount -= 1;
	canFire = false;
	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &AGun::ReadyFire, shotDelay, false);
}

void AGun::ReadyFire()
{
	canFire = true;
}

bool AGun::ApplyDamage(FHitResult* hit)
{
	if (hit->GetActor() != nullptr) {
		//GetWorld()->DestroyActor(HitResult.GetActor());
		TSubclassOf<UHpComponent> hpc;
		UObject* c = hit->GetActor()->GetDefaultSubobjectByName("Hp");

		UHpComponent* hp = Cast<UHpComponent>(c);

		if (hp != nullptr) {
			hp->InputDamage(damage);
			return true;
		}
	}
	return false;
}

bool AGun::RayCasting(UCameraComponent* cameraComponent)
{
	FVector Start = cameraComponent->GetComponentLocation();
	FVector End = cameraComponent->GetForwardVector().
		RotateAngleAxis(FMath::RandRange(-gunAngleRange, gunAngleRange),
			FVector(FMath::RandRange(-1.f, 1.f),
				FMath::RandRange(-1.f, 1.f),
				FMath::RandRange(-1.f, 1.f))) * 100000 + Start;

	FHitResult HitResult;

	UKismetSystemLibrary::
		LineTraceSingleForObjects(
			GetWorld(), Start, End, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, false, FLinearColor::Red, FLinearColor::Green, 0.5f);


	//GetWorld()->SpawnActor()
	//FActorSpawnParameters spawnParams;
	//FRotator rotator;
	//FVector spawnLocation = FVector::ZeroVector;

	//GetWorld()->SpawnActor<ABulletHole>(ABulletHole::StaticClass(), spawnLocation, rotator, spawnParams);



	return ApplyDamage(&HitResult);
}


void AGun::Reload() {

	if (!isReload) {
		GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGun::EndReload, reloadTime, false);
		isReload = true;
	}
}

void AGun::CancleReload()
{
	if (isReload) {
		GetWorldTimerManager().ClearTimer(reloadTimerHandle);
		isReload = false;
	}
}

void AGun::EndReload()
{
	if (isReload) {
		isReload = false;
		curAmmoCount = maxAmmoCount;
		GetWorldTimerManager().ClearTimer(reloadTimerHandle);
	}
}
