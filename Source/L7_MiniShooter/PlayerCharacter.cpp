// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setting up the Camera
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.0f; // The camera follow distance
	CameraArm->bUsePawnControlRotation = true; // Rotate arm based on the controller
	CameraArm->SocketOffset = FVector(0.0f, 75.0f, 50.0f); // Offset to the right and above the character
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 5.0f;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	// Aim Settings
	baseFOV = PlayerCamera->FieldOfView;
	aimFOV = 25.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}
