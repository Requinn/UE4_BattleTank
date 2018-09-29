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
	virtual void BeginPlay() override;
	void ApplySidewaysForce();
	void DriveTrack();
	float CurrentThrottle = 0;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
