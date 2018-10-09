// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankController.generated.h" //must be the last include

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairY = 0.3333f;
	UPROPERTY()
	float LineTraceRange = 10000000;
	
	UTankAimingComponent* AimingComponent;

	UFUNCTION()
	void HandleDeath();

	//return an OUT parameter, true if it hits a landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	//moves barrel to aim towards the crosshair is
	void AimTowardsCrosshair();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	
	
};
