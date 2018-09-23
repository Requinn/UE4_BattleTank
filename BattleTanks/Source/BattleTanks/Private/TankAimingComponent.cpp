// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h" //this is needed when we need to call methods in the barrel, where the forward declaration is not enough
#include "TankTurret.h"
#include "TankProjectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	if (ensure(BarrelToSet)) {
		Barrel = BarrelToSet;
	}
	if (ensure(TurretToSet)) {
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
void UTankAimingComponent::AimAt(FVector AimLocation) {
	if (!ensure(Barrel)) {
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

//Fires the tank cannon
void UTankAimingComponent::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime; //if the current time - the time we last fired is greater than the time we set to reload
																			  //fire only once every X seconds
	if (!ensure(Barrel)) { return; }
	if (isReloaded) {
		//fire a projectile at the socket location
		//spawn a projectileblueprint obj at the barrel's projectilpoint socket location and with its rotation
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectilePoint")), Barrel->GetSocketRotation(FName("ProjectilePoint")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

//Move the barrel using a direction that is passed in
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Convert the aimDirection unit to a rotation
	//apply the rotation to the barrel
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}