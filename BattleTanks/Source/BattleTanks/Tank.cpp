// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// No need to protect pointers added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet; //save a local ref to help spawn projectiles
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

//Fires the tank cannon
void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime; //if the current time - the time we last fired is greater than the time we set to reload
	//fire only once every X seconds
	if (Barrel && isReloaded) {
		//fire a projectile at the socket location
		UE_LOG(LogTemp, Warning, TEXT("Pew"));
		//spawn a projectileblueprint obj at the barrel's projectilpoint socket location and with its rotation
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectilePoint")), Barrel->GetSocketRotation(FName("ProjectilePoint")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

//tell our Aim Component who is aiming at what
void ATank::AimAt(FVector AimLocation) {
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed); //Aim at that location, and use a given Launchspeed to calculate our trajectory
}

