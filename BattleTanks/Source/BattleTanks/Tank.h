// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class ATankProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
public:
	//aim at this location
	virtual void AimAt(FVector AimLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = TankAction)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	//EditDefaultsOnly will modify this value on ALL Tanks, editable only in blueprints
	//EditAnywhere will modify this value PER Tank
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000; //1 km/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr; //local barrel ref to spawn the projectile
	
	double LastFireTime = 0;
	
};
