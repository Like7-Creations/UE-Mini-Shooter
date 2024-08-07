// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class L7_MINISHOOTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:

	// Camera Variables
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	float aimFOV;

	float baseFOV;
	
};
