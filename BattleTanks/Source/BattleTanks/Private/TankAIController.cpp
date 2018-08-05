// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI POESSESING: %s"), *ControlledTank->GetName());
		UE_LOG(LogTemp, Warning, TEXT("AI FOUND PLAYER : %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NO aI TANK FOUND"));
	}
}

//get the tank that we are controlling
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

//Get the player's pawn
ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); //The mistake was getting the controller, and casting the controlelr to Tank wasn't workiing properly
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


