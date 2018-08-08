// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h" //this is needed when we need to call methods in the barrel, where the forward declaration is not enough
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

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
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s is aimint at %s"),*TankName, *AimDirection.ToString()); //only log when we get a result
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aiming at nothing"));
	}
}

//Move the barrel using a direction that is passed in
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert the aimDirection unit to a rotation
	//apply the rotation to the barrel
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(5);
}