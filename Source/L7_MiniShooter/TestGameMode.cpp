// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerStart.h"
#include "TimerManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerController.h"
#include "GameModeHUD.h"

ATestGameMode* ATestGameMode::Get()
{
    return Cast<ATestGameMode>(UGameplayStatics::GetGameMode(GWorld));
}

ATestGameMode::ATestGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerCharacter(TEXT("/Game/BluePrints/Characters/BP_BaseCharacter"));
    DefaultPawnClass = PlayerCharacter.Class;
    HUDClass = AGameModeHUD::StaticClass();
}

void ATestGameMode::BeginPlay()
{
    Super::BeginPlay();

    GetSpawnPoints();
    SpawnCharacters();
    SetInputStateOfAllCharacters(false);

    CountdownDuration = 5.0f;
    CountdownTime = CountdownDuration;
    GetWorld()->GetTimerManager().SetTimer(TimerHandel_Countdown, this, &ATestGameMode::UpdateCountDown, 1.0f, false);
}

void ATestGameMode::UpdateCountDown()
{
    if (CountdownTime > 0)
    {
        CountdownTime--;

        // Get the HUD and update the countdown
        AGameModeHUD* GameHUD = Cast<AGameModeHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
        if (GameHUD)
        {
            GameHUD->SetCountdown(CountdownTime);
        }

        GetWorld()->GetTimerManager().SetTimer(TimerHandel_Countdown, this, &ATestGameMode::UpdateCountDown, 1.0f, false);
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandel_Countdown);
        StartGame();
    }
}

void ATestGameMode::GetSpawnPoints()
{
    // Get all actors of type "PlayerStart" in the level (or any other custom spawn point class)
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
}

void ATestGameMode::SpawnCharacters()
{
    if (SpawnPoints.Num() < 5)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough spawn points for all characters!"));
        return;
    }

    // Shuffle the spawn points to randomize spawn locations
    for (int32 i = 0; i < SpawnPoints.Num(); i++)
    {
        int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
        SpawnPoints.Swap(i, RandomIndex);
    }

    // Spawn the player
    ABaseCharacter* PlayerCharacter = GetWorld()->SpawnActor<ABaseCharacter>(PlayerCharacterClass, SpawnPoints[0]->GetActorLocation(), SpawnPoints[0]->GetActorRotation());
    if (PlayerCharacter)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController)
        {
            PlayerController->Possess(PlayerCharacter);
        }
    }

    // Spawn AI characters
    for (int32 i = 1; i <= 4; i++)
    {
        GetWorld()->SpawnActor<ABaseCharacter>(AICharacterClass, SpawnPoints[i]->GetActorLocation(), SpawnPoints[i]->GetActorRotation());
    }

    // Assign random names to all characters
    AssignRandomNames();
}

void ATestGameMode::AssignRandomNames()
{

    FString FilePath = FPaths::ProjectContentDir() + "CharacterNames.txt";
    TArray<FString> Names;

    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        FFileHelper::LoadFileToStringArray(Names, *FilePath);
    }

    // Get all characters in the world (both player and AI)
    TArray<AActor*> Characters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Characters);

    // Assign random names to each character
    for (AActor* Actor : Characters)
    {
        ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);
        FString Name = "Dummy";
        if (Character)
        {

            if (Names.Num() > 0)
            {
                int32 RandomIndex = FMath::RandRange(0, Names.Num() - 1);
                Name = Names[RandomIndex];
                Names.Remove(Name);
            }
            Character->AssignName(Name);
        }
    }
}

void ATestGameMode::HandleCountdown()
{
    // Disable player input and AI movement
    if (CountdownTime > 0)
    {
        CountdownTime -= 1.0f;
        GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ATestGameMode::HandleCountdown);
    }
    else
    {
        // Re-enable player input and AI movement
        StartGame();
    }
}

void ATestGameMode::SetInputStateOfAllCharacters(bool bState)
{
    TArray<AActor*> Characters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Characters);

    // Loop through all characters in the world and disable input
    for (int i = 0; i < Characters.Num(); i++)
    {
        ABaseCharacter* Character = Cast<ABaseCharacter>(Characters[i]);
        if (Character)
        {
            Character->SetCharacterInputEnabled(bState);
        }
    }
}

void ATestGameMode::StartGame()
{
    SetInputStateOfAllCharacters(true);
}

