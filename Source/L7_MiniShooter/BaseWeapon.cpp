// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Logging/StructuredLog.h"
#include "GameFramework/PlayerController.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	DamagePerShot = 25.f;
	MagazineCapacity = 30;
	BulletsInMagazine = MagazineCapacity;
	MagazinesCarried = 3;
	RateOfFire = 50.f;
	ReloadTime = 2.f;
	bIsAutomatic = true;

	ShotInterval = 60.f / RateOfFire;
	bCanFire = true;
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::Reload()
{
	StopFire();

	if (MagazinesCarried > 0 && BulletsInMagazine < MagazineCapacity)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &ABaseWeapon::FinishReload, ReloadTime, false);
	}
}

void ABaseWeapon::FinishReload()
{
	if (MagazinesCarried > 0)
	{
		MagazinesCarried--;
		BulletsInMagazine = MagazineCapacity;
	}
}

void ABaseWeapon::ResetFireState()
{
	bCanFire = true;
}

void ABaseWeapon::StartFire()
{
	if (bCanFire)
	{
		Fire();
		if (bIsAutomatic)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_AutomaticShots, this, &ABaseWeapon::Fire, ShotInterval, true);
		}
	}
	else
	{
		Fire();
	}
}

void ABaseWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_AutomaticShots);
}

void ABaseWeapon::Fire()
{
	if (!bCanFire)
	{
		return;
	}

	if (BulletsInMagazine > 0)
	{
		BulletsInMagazine--;

		HandleShot();

		if (BulletsInMagazine <= 0)
		{
			StopFire();
			Reload();
		}
	}
	else
	{
		StopFire();
		Reload();
	}

	bCanFire = false;
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ABaseWeapon::ResetFireState, ShotInterval, true);

	if (!bIsAutomatic)
	{
		StopFire();
	}
}

void ABaseWeapon::HandleShot()
{
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorForwardVector() * 10000.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(ShootingCharacter);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);

	FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, 1.0f, 0, 1.0f);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			//if ()
			//{
			//	// Apply damage to the hit character
			//}
		}
	}
}

void ABaseWeapon::SetCharacter(AActor* Shooter)
{
	ShootingCharacter = Shooter;
}

int ABaseWeapon::GetAmmo()
{
	return BulletsInMagazine;
}

int ABaseWeapon::GetTotalAmmo()
{
	return MagazineCapacity * MagazinesCarried;
}