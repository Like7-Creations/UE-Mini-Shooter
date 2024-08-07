#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
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
	// Movement Functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void Jump();

	//
	// Stat Functions
	void TakeDamage(int Value);
	void Heal(int Value);
	void Death();
	int GetHealth();
	int GetMaxHealth();
	void AssignName(FString Text);

private:
	bool bIsSprinting;
	void UpdateStamina(float DeltaTime);
};
