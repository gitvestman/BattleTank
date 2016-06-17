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
    auto MyTank = GetControlledTank();
    auto PlayerTank = GetPlayerController();
    if (PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController %s"), *PlayerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController found"));
    }
}

ATank* ATankAIController::GetPlayerController() const {
    auto PlayerPawn = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerPawn) {
        return Cast<ATank>(PlayerPawn->GetControlledTank());
    }
    return nullptr;
}

