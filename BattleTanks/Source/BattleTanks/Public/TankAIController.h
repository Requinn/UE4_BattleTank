// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
public:
	GENERATED_BODY()
	
private:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	//how close can the tank get to the player
	float AcceptanceRadius = 30;
	
};
