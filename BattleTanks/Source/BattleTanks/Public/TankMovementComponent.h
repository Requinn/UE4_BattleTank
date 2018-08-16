// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
protected:

public:
	//Throw is how far forward and back the controller moves
	UFUNCTION(BlueprintCallable, Category = TankMovement)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftToSet, UTankTrack* RightToSet);
	UFUNCTION(BlueprintCallable, Category = TankMovement)
	void IntendTurnRight(float Rotation);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
