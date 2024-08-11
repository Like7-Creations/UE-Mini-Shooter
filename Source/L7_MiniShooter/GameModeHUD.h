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

	void SetCountdown(int32 NewCountdown);

private:
	int32 Countdown;
	
	UPROPERTY(EditAnywhere, Category = "Texts")
	UFont* CountDownFont;
	
};
