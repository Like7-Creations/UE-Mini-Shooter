// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Default Values Setup
	CharacterName = "Dummy";
	Health = 100;
	Stamina = 100.0f;
	MaxStamina = 100.0f;
	StaminaRechargeRate = 10.0f;
	StaminaConsumptionRate = 2.0f;
	Speed = 600.0f;
	SprintMultiplier = 2.5f;
	bIsSprinting = false;
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	// Name Text Setup
	NameTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	NameTextRender->SetupAttachment(RootComponent);
	NameTextRender->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	NameTextRender->SetHorizontalAlignment(EHTA_Center);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Movement Functions

void ABaseCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABaseCharacter::StartSprint()
{
	if (Stamina > 0.f)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = Speed * SprintMultiplier;
	}
}

void ABaseCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ABaseCharacter::Jump()
{
	ACharacter::Jump();
}

