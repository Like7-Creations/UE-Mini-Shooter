// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameModeHUD.generated.h"

/**
 * 
 */
UCLASS()
class L7_MINISHOOTER_API AGameModeHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void DrawHUD() override;

	void SetCountdown(int NewCountdown);
	void SetCurrentAmmo(int Ammo);
	void SetTotalAmmo(int Ammo);
	void SetMaxStamina(float Max);
	void SetCurrentStamina(float Stamina);

private:
	int Countdown;
	int CurrentAmmo;
	int TotalAmmo;
	float MaxStamina;
	float CurrentStamina;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	UFont* CountDownFont;

	UPROPERTY(EditAnywhere, Category = "UI")
	UFont* AmmoFont;

	UPROPERTY(EditAnywhere, Category = "UI")
	UTexture2D* CrossHair;
	
};
