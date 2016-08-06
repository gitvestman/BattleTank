// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

    if (ensure(PlayerTank))
    {
        // TODO Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);
        // Aim towards playet
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
        
		ControlledTank->Fire(); // TODO Don't fire every frame
    }
}


