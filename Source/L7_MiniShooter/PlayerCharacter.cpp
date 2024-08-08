// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setting up the Camera
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.0f; // The camera follow distance
	CameraArm->bUsePawnControlRotation = true; // Rotate arm based on the controller
	CameraArm->SocketOffset = FVector(0.0f, 50.0f, 50.0f); // Offset to the right and above the character
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Movement Controls
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Movement);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
	Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartSprint);
	Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);
	Input->BindAction(AimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartAim);
	Input->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopAim);

	// Weapon Controls
	Input->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartFireWeapon);
	Input->BindAction(FireAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopFireWeapon);
	Input->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReloadWeapon);
	Input->BindAction(SwitchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SwitchWeapon);
}

void APlayerCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FVector ForwardDirection = GetActorForwardVector();
		const FVector RightDirection = GetActorRightVector();

		const FVector MovementDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
		AddMovementInput(MovementDirection, 1.0f);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::StartAim()
{
	PlayerCamera->SetFieldOfView(aimFOV);
}

void APlayerCharacter::StopAim()
{
	PlayerCamera->SetFieldOfView(baseFOV);
}

void APlayerCharacter::SwitchWeapon(const FInputActionValue& Value)
{
	float fIndex = Value.Get<float>();
	int WeaponIndex = (int)fIndex;

	if (Weapons.IsValidIndex(WeaponIndex - 1))
	{
		EquipWeapon(WeaponIndex - 1);
	}
}
