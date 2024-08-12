// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"


void AGameModeHUD::BeginPlay()
{
    Super::BeginPlay();
    Countdown = 5;
    CurrentAmmo = 0;
    TotalAmmo = 0;
    MaxStamina = 100.0f;
    CurrentStamina = 100.0f;
    Countdown = 5;
}

void AGameModeHUD::DrawHUD()
{
    Super::DrawHUD();

    // Start Countdown UI
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

    // Player Ammo UI
    FString AmmoText = FString::Printf(TEXT("%d : %d"), CurrentAmmo, TotalAmmo);
    FVector2D AmmoPosition = FVector2D(Canvas->SizeX - 100.0f, Canvas->SizeY - 50.0f);

    FCanvasTextItem AmmoItem(AmmoPosition, FText::FromString(AmmoText), AmmoFont, FLinearColor::White);
    AmmoItem.bCentreX = false;
    AmmoItem.bCentreY = false;

    Canvas->DrawItem(AmmoItem);

    // Player Stamina UI
    float StaminaBarWidth = 20.0f;
    float StaminaBarHeight = 500.0f;
    float StaminaPercentage = CurrentStamina / MaxStamina;

    FVector2D StaminaBarPosition = FVector2D(20.0f, Canvas->SizeY - 520.0f);
    FVector2D StaminaBarSize = FVector2D(StaminaBarWidth, StaminaBarHeight * StaminaPercentage);

    FCanvasBoxItem StaminaBarBg(StaminaBarPosition, FVector2D(StaminaBarWidth, StaminaBarHeight));
    StaminaBarBg.SetColor(FLinearColor::Gray);
    Canvas->DrawItem(StaminaBarBg);

    FCanvasBoxItem StaminaBar(StaminaBarPosition, StaminaBarSize);
    StaminaBar.SetColor(FLinearColor::Yellow);
    Canvas->DrawItem(StaminaBar);

    //CrossHair
    if (CrossHair && Countdown <= 0)
    {
        FVector2D Center(Canvas->SizeX / 2.0f, Canvas->SizeY / 2.0f);
        float ScaleFactor = 0.3f;

        FVector2D CrosshairSize = FVector2D(CrossHair->GetSurfaceWidth() * ScaleFactor, CrossHair->GetSurfaceHeight() * ScaleFactor);
        FVector2D CrosshairDrawPosition(Center.X - (CrosshairSize.X / 2), Center.Y - (CrosshairSize.Y / 2));


        FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairSize, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        TileItem.Texture = CrossHair->GetResource();
        Canvas->DrawItem(TileItem);
    }
}

void AGameModeHUD::SetCountdown(int NewCountdown)
{
    Countdown = NewCountdown;
}

void AGameModeHUD::SetCurrentAmmo(int Ammo)
{
    CurrentAmmo = Ammo;
}

void AGameModeHUD::SetTotalAmmo(int Ammo)
{
    TotalAmmo = Ammo;
}

void AGameModeHUD::SetMaxStamina(float Max)
{
    MaxStamina = Max;
}

void AGameModeHUD::SetCurrentStamina(float Stamina)
{
    CurrentStamina = Stamina;
}
