// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>(); //Remeber to use GetPawn()-> or else it won't find the component

	if (!ensure(PlayerTank && AimingComponent)) { return; }

	if (FVector::DistSquared(PlayerTank->GetActorLocation(), GetPawn()->GetActorLocation()) > AcceptanceRadius * AcceptanceRadius) {
		MoveToActor(PlayerTank, AcceptanceRadius);
	}

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//fire only when locked
	if (AimingComponent->GetFiringState() == EFiringStatus::Ready) {
		AimingComponent->Fire();
	}
}
