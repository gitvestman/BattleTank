// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

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
    // Find the crosshair position
    // De-project the screen position o fthe croshair
    // Line-trace along that line and see what we hit
    
    if (GetLookVectorHitLocation(OUT HitLocation))
    {
        return true;
    }
    
    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation) {
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,
                                    ViewportSizeY * CrossHairYLocation);
    
    FVector LookDirection;
    if (!GetLookDirection(ScreenLocation, OUT LookDirection)) {
        return false;
    }
    // Line Trace
    FHitResult Hit;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    if (GetWorld()->LineTraceSingleByChannel(
                                         OUT Hit,
                                         StartLocation,
                                         EndLocation,
                                         ECollisionChannel::ECC_WorldStatic
                                         ))
    {
        HitLocation = Hit.Location;
        return true;
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
    FVector WorldLocation; // Ignore camera world location
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
                                          OUT WorldLocation,  OUT LookDirection);
}

