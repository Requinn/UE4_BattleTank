// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftToSet, UTankTrack* RightToSet) {
	if (!LeftToSet || !RightToSet) {
		return;
	}
	LeftTrack = LeftToSet;
	RightTrack = RightToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Rotation) {
	LeftTrack->SetThrottle(Rotation); //left moves forward
	RightTrack->SetThrottle(-Rotation); //right moves back
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("%s MoveRequest: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString())
}


