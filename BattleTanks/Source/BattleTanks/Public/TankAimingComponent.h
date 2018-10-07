// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//A forward declaration, allowing us to get a reference to this class without doing an include
class UTankBarrel; //hold properties for barrel 
class UTankTurret;
class ATankProjectile;

UENUM()
enum class EFiringStatus : uint8 { Ready, Aiming, Reloading, OutofAmmo};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet);
	UFUNCTION(BlueprintCallable, Category = TankAction)
	void Fire();
	//aim at something
	void AimAt(FVector AimLocation);
	void MoveBarrelTowards(FVector Direction);
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000; //1 km/s

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FireStatus = EFiringStatus::Reloading;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction) override;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;
	bool IsBarrelMoving();
	//EditDefaultsOnly will modify this value on ALL Tanks, editable only in blueprints
	//EditAnywhere will modify this value PER Tank
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 ammoRemaining = 5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATankProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

};
