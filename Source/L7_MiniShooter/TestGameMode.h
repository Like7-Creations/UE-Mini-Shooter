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
	static ATestGameMode* Get();

	virtual void BeginPlay() override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    TArray<AActor*> SpawnPoints;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    TSubclassOf<ABaseCharacter> PlayerCharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    TSubclassOf<ABaseCharacter> AICharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    float CountdownDuration;

    int CountdownTime;
    FTimerHandle TimerHandel_Countdown;
    void UpdateCountDown();
    void StartGame();
    void SpawnCharacters();
    void AssignRandomNames();
    void SetInputStateOfAllCharacters(bool bState);

public:
    void GetSpawnPoints();
    void HandleCountdown();

};
