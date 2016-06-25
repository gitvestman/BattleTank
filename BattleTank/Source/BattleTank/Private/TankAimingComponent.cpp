// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
            this,
            OUT OutLaunchVelocity,
            StartLocation,
            AimLocation,
            LaunchSpeed,
            false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace
    );
    
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found %f"), Time, AimDirection.Y);
    }
    else
    {
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Work out difference between current barrel rotaion and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimRotator = AimDirection.Rotation();
    auto DeltaRotator = AimRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
}


