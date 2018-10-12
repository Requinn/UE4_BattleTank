// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * used to the set the maximu driving force of the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	//max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TankMaxDrivingForce = 400000; //F = MA, 40T tank at 1G acceleration
	
private:
	UTankTrack();
	void DriveTrack(float CurrentThrottle);
	TArray<class ASpringWheel*> GetWheels() const;
};
