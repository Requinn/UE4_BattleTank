// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h" //used to implement OnDeath
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	//only do stuff when we have a inbound pawn to possess
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleDeath);
	}
}

void ATankAIController::HandleDeath() {
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank has died."));
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
