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

ATestGameMode::ATestGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerCharacter(TEXT("/Game/BluePrints/Characters/BP_BaseCharacter"));
    DefaultPawnClass = PlayerCharacter.Class;
}

void ATestGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> SpawnPoints;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);

    ABaseCharacter* PlayerCharacter = GetWorld()->SpawnActor<ABaseCharacter>(PlayerCharacterClass, SpawnPoints[0]->GetActorLocation(), SpawnPoints[0]->GetActorRotation());
    if (PlayerCharacter)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController)
        {
            PlayerController->Possess(PlayerCharacter);
        }
    }

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


