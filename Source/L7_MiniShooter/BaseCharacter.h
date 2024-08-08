#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "BaseWeapon.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter.generated.h"

UCLASS()
class L7_MINISHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Standard Character Information
	UPROPERTY(VisibleAnywhere, Category = "Character")
	FString CharacterName;

	UPROPERTY(EditAnywhere, Category = "Character")
	UTextRenderComponent* NameTextRender;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	int Health;

	UPROPERTY(VisibleAnywhere, Category = "Character/Stats")
	int CurrentHealth;

	bool bIsDead;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Character/Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	float StaminaRechargeRate;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	float StaminaConsumptionRate;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Character/Stats")
	float SprintMultiplier;

protected:
	// Weapon Information
	UPROPERTY(EditAnywhere, Category = "Character/Weapons")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

	UPROPERTY(EditAnywhere, Category = "Character/Weapons")
	TArray<ABaseWeapon*> Weapons;

	UPROPERTY(VisibleAnywhere, Category = "Character/Weapons")
	int CurrentWeaponIndex;
	
	// Movement Functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void Jump();

	// Weapon Functions
	void FireWeapon();
	void StartFireWeapon();
	void StopFireWeapon();
	void ReloadWeapon();
	void EquipWeapon(int Index);
	int GetMagazineAmmo();
	int GetTotalAmmo();

	// Stat Functions
	void Heal(int Value);
	void Death();
	int GetHealth();
	int GetMaxHealth();
	
	bool bIsSprinting;
	void UpdateStamina(float DeltaTime);

public:
	void AssignName(FString Text);
	void TakeDamage(int Value);


};
