// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()
		
public:
	ATank* GetControlledTank() const;

	//moves barrel to aim towards the crosshair is
	void AimTowardsCrosshair();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	
	
};
