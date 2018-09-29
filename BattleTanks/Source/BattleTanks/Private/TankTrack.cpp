// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() {
	//calculate slippage by using a dot product against our right vector
	//dot product against 90* is 0, which means we are going straight and don't need a correction
	//dot product that is not against 90* will return a value that we take the negative of find the direction we should be adjusting into

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	float slippage = FVector::DotProduct(GetComponentVelocity(), GetRightVector()); //if slippage is 0, we are perfectly aligned forward
	auto correctionAcceleration = -slippage / DeltaTime * GetRightVector(); //divide the slippage value we have by the time passing and subtract it to reduce our speed;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (correctionAcceleration * Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->GetMass()) / 2;
	TankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack() {
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce; //calculate the force we apply
	FVector ForceLocation = GetComponentLocation();	//get where we apply it
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //get what we apply it to, We get a scenecomponent from the RootComponent, so we cast to a UPrim so we have access to adding a force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
