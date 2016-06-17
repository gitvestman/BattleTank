// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATank*  GetControlledTank() const;
	
private:
    void BeginPlay() override;
    
    virtual void Tick( float DeltaSeconds ) override;
    
    // Move the barrel towards aim
    void AimTowardsCrosshair();
    
    // Return true if hit landscape
    bool GetSightRayHitLocation(FVector & HitLocation);
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector & HitLocation);
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.3;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000;
};
