// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// No need to protect pointers added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet; //set this locally
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
	if (Barrel) {
		//fire a projectile at the socket location
		UE_LOG(LogTemp, Warning, TEXT("Pew"));
		GetWorld()->SpawnActor<ATankProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectilePoint")), Barrel->GetSocketRotation(FName("ProjectilePoint")));
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

