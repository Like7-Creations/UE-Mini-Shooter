
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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

	CurrentHealth = Health;
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	}

	// Add Weapons to Character
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	for (int i = 0; i < WeaponClasses.Num(); i++)
	{
		ABaseWeapon* TempWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClasses[i]);
		TempWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));
		TempWeapon->SetActorEnableCollision(false);
		TempWeapon->SetCharacter(this);
		Weapons.Add(TempWeapon);
		EquipWeapon(i);
	}
	EquipWeapon(0);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector Direction = CameraLocation - NameTextRender->GetComponentLocation();
		Direction.Normalize();

		FRotator NewRotation = Direction.Rotation();
		NewRotation.Pitch = 0.0f; 

		NameTextRender->SetWorldRotation(NewRotation);
	}
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

// Weapon Functions

void ABaseCharacter::EquipWeapon(int Index)
{
	if (Weapons.IsValidIndex(Index))
	{
		for (ABaseWeapon* Weapon : Weapons)
		{
			if (Weapon)
			{
				Weapon->SetActorHiddenInGame(true);
			}
		}

		ABaseWeapon* SelectedWeapon = Weapons[Index];
		if (SelectedWeapon)
		{
			SelectedWeapon->SetActorHiddenInGame(false);
		}
		CurrentWeaponIndex = Index;
	}
}

void ABaseCharacter::FireWeapon()
{
	if (Weapons[CurrentWeaponIndex])
	{
		Weapons[CurrentWeaponIndex]->Fire();
	}
}

void ABaseCharacter::StartFireWeapon()
{
	if (Weapons[CurrentWeaponIndex])
	{
		Weapons[CurrentWeaponIndex]->StartFire();
	}
}

void ABaseCharacter::StopFireWeapon()
{
	if (Weapons[CurrentWeaponIndex])
	{
		Weapons[CurrentWeaponIndex]->StopFire();
	}
}

void ABaseCharacter::ReloadWeapon()
{
	if (Weapons[CurrentWeaponIndex])
	{
		Weapons[CurrentWeaponIndex]->Reload();
	}
}

int ABaseCharacter::GetMagazineAmmo()
{
	return Weapons[CurrentWeaponIndex]->GetAmmo();
}

int ABaseCharacter::GetTotalAmmo()
{
	return Weapons[CurrentWeaponIndex]->GetTotalAmmo();
}