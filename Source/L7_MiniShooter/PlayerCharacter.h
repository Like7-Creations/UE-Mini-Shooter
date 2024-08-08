// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputLibrary.h"
#include "EnhancedInputComponent.h"
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
	
	void Movement(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SwitchWeapon(const FInputActionValue& Value);
	void StartAim();
	void StopAim();

	// Mapping reference

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Actions Reference

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SwitchAction;
};
