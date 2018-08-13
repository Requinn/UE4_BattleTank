// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	Throttle = FMath::Clamp<float>(Throttle, 0, 1);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * TankMaxDrivingForce; //calculate the force we apply
	FVector ForceLocation = GetComponentLocation();	//get where we apply it
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //get what we apply it to, We get a scenecomponent from the RootComponent, so we cast to a UPrim so we have access to adding a force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
