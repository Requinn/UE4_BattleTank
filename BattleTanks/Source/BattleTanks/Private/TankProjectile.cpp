// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankProjectile.h"


// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//set the projectile velocity to what we set in the tank and activate it
void ATankProjectile::LaunchProjectile(float speed) {
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovementComponent->Activate();
}

