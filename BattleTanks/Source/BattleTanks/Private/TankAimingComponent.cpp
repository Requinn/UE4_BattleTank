// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h" //this is needed when we need to call methods in the barrel, where the forward declaration is not enough
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (BarrelToSet) {
		Barrel = BarrelToSet;
	}
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (TurretToSet) {
		Turret = TurretToSet;
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



//given a location and launch speed, calculate where we are aiming at
void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed) {
	if (!Barrel) {
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectilePoint"));

	//use this function to generate a suggested projectile velocity for it to hit somepoint with X force
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

//Move the barrel using a direction that is passed in
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert the aimDirection unit to a rotation
	//apply the rotation to the barrel
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}