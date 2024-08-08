// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class L7_MINISHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float DamagePerShot;

    UPROPERTY(VisibleAnywhere, Category = "Weapon Stats")
    int BulletsInMagazine;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int MagazinesCarried;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int MagazineCapacity;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float RateOfFire;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float ReloadTime;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    bool bIsAutomatic;

    float ShotInterval;

    UPROPERTY(VisibleAnywhere, Category = "Weapon Stats")
    bool bCanFire;

    FTimerHandle TimerHandle_AutomaticShots;
    FTimerHandle TimerHandle_TimeBetweenShots;
    FTimerHandle TimerHandle_Reload;

    AActor* ShootingCharacter;

    void HandleShot();

    UFUNCTION()
    void FinishReload();

    UFUNCTION()
    void ResetFireState();

public:

    // Function to reload the weapon
    UFUNCTION(Category = "Weapon Functions")
    virtual void Reload();

    // Function to shoot the weapon
    UFUNCTION(Category = "Weapon Functions")
    virtual void StartFire();

    UFUNCTION(Category = "Weapon Functions")
    virtual void StopFire();

    virtual void Fire();

    int GetAmmo();
    int GetTotalAmmo();
    void SetCharacter(AActor* Shooter);
	
};
