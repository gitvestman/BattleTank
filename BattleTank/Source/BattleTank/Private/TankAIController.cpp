// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) && !ensure(ControlledTank)) { return;  }
    
	// TODO Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
    // Aim towards playet
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
       
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
}


