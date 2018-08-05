// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankController.h"
#include "Tank.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("POESSESING: %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NO TANK FOUND"));
	}
}

//get the tank that we are controlling
ATank* ATankController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATankController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; } //exit if we don't exist

	//get world location through a linecast through the point on the screen
	//if the line cast hits the world, aim towards that point
}

