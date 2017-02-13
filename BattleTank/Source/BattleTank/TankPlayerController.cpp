// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
		// Subscribe our local method to the tank's death event
	}
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return;  }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

    FVector HitLocation; // out parameter
    if (GetSightRayHitLocation(OUT HitLocation))
    {
		AimingComponent->AimAt(HitLocation);
   }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,
		ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) 
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    if (GetWorld()->LineTraceSingleByChannel(
                                         HitResult,
                                         StartLocation,
                                         EndLocation,
                                         ECollisionChannel::ECC_Visibility
                                         ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
	HitLocation = FVector(0);
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
    FVector WorldLocation; // Ignore camera world location
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
                                          OUT WorldLocation,  OUT LookDirection);
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}
