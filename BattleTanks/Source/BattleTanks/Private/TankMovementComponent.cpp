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
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Rotation) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Rotation); //left moves forward
	RightTrack->SetThrottle(-Rotation); //right moves back
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//get the forward vector and the normal of the direction we wish to move
	auto TankForward = GetOwner()->GetActorForwardVector();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//calculate their dot product to find how much of an angle we should be at
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	//calculate how much we should turn by using a cross
	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(TurnThrow); //the resulting crossproduct is stored in the Z, and we rotate according to this value
}


