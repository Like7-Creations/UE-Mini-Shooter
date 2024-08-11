// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"

void AGameModeHUD::BeginPlay()
{
    Super::BeginPlay();
    Countdown = 5;
}

void AGameModeHUD::DrawHUD()
{
    Super::DrawHUD();

    if (Countdown > 0)
    {
        FString CountdownText = FString::Printf(TEXT("%d"), Countdown);
        FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

        FVector2D TextPosition = FVector2D(ScreenDimensions.X / 2.0f, ScreenDimensions.Y / 2.0f);

        FCanvasTextItem TextItem(TextPosition, FText::FromString(CountdownText), CountDownFont, FLinearColor::White);
        TextItem.bCentreX = true;
        TextItem.bCentreY = true;

        Canvas->DrawItem(TextItem);
    }
}

void AGameModeHUD::SetCountdown(int32 NewCountdown)
{
    Countdown = NewCountdown;
}

