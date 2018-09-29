// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h" //this is needed when we need to call methods in the barrel, where the forward declaration is not enough
#include "TankTurret.h"
#include "TankProjectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FireStatus;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction) {
	if (ammoRemaining <= 0) {
		FireStatus = EFiringStatus::OutofAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime) { //if the current time - the time we last fired is greater than the time we set to reload
		FireStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FireStatus = EFiringStatus::Aiming;
	}
	else {
		FireStatus = EFiringStatus::Ready;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	//return the opposite, because we want to know if theyre not the same, thus moving
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

int UTankAimingComponent::GetAmmoCount() const{
	return ammoRemaining;
}

//Fires the tank cannon
void UTankAimingComponent::Fire() {
	if (FireStatus == EFiringStatus::Ready || FireStatus == EFiringStatus::Aiming) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//fire a projectile at the socket location
		//spawn a projectileblueprint obj at the barrel's projectilpoint socket location and with its rotation
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectilePoint")), Barrel->GetSocketRotation(FName("ProjectilePoint")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		ammoRemaining--;
	}
}

//Move the barrel using a direction that is passed in
void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Convert the aimDirection unit to a rotation
	//apply the rotation to the barrel
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = Direction.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

	//If the delta has to rotate past the halfway point, take the shorter route by going in the opposite direction
	if (FMath::Abs(DeltaRotation.Yaw) > 180.0) {
		Turret->Rotate(-DeltaRotation.Yaw);
	}
	else {
		Turret->Rotate(DeltaRotation.Yaw);
	}
	
}