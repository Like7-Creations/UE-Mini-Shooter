
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseCharacter::ABaseCharacter()
{
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

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);
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

// Stat Functions

void ABaseCharacter::UpdateStamina(float DeltaTime)
{
	if (bIsSprinting)
	{
		Stamina -= 20.f * StaminaConsumptionRate * DeltaTime;
		if (Stamina <= 0.f)
		{
			Stamina = 0.f;
			StopSprint();
		}
	}
	else if (Stamina < MaxStamina)
	{
		Stamina += StaminaRechargeRate * DeltaTime;
		if (Stamina > MaxStamina)
		{
			Stamina = MaxStamina;
		}
	}
}

void ABaseCharacter::TakeDamage(int Value)
{
	if (!bIsDead)
	{
		if (CurrentHealth - Value > 0)
		{
			CurrentHealth -= Value;
		}
		else
		{
			CurrentHealth = 0;
			Death();
		}
	}
}

void ABaseCharacter::Heal(int Value)
{
	if (CurrentHealth + Value <= Health) {
		CurrentHealth += Value;
	}
	else {
		CurrentHealth = Health;
	}
}

void ABaseCharacter::Death()
{
	bIsDead = true;
}

void ABaseCharacter::AssignName(FString Text)
{
	CharacterName = Text;
	if (NameTextRender)
	{
		NameTextRender->SetText(FText::FromString(Text));
	}
}

int ABaseCharacter::GetHealth()
{
	return CurrentHealth;
}

int ABaseCharacter::GetMaxHealth()
{
	return Health;
}