// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseCharacter.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class L7_MINISHOOTER_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATestGameMode();

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ABaseCharacter> PlayerCharacterClass;
	
	void AssignRandomNames();
	
};
