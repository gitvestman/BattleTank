// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"


ATank*  ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("TankAIController BeginPlay()"));
    auto PlayerTank = GetPlayerTank();
    if (PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController %s"), *PlayerTank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController found"));
    }
}

void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);
    if (GetPlayerTank())
    {
        // Move towards the player
        
        // Aim towards playet
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        
        // Fire if ready
    }
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerPawn = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerPawn) {
        return PlayerPawn->GetControlledTank();
    }
    return nullptr;
}

