// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "SpringWheel.h"
#include "SpawnActorComponent.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle) {
	auto ForceApplied = CurrentThrottle * TankMaxDrivingForce; //calculate the force we apply
	auto wheels = GetWheels();
	auto forcePerWheel = ForceApplied / wheels.Num();

	for (ASpringWheel* wheel : wheels) {
		wheel->AddDrivingForce(forcePerWheel);
	}
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> out;			//out array to hold all gathered children
	TArray<ASpringWheel*> returnArray;		//array to return actors
	GetChildrenComponents(true, out);		//get the children
	for (auto actor : out) {
		auto spawnChild = Cast<USpawnActorComponent>(actor); //get the child's spawnActorcomponent
		if (!spawnChild) { continue; }						//skip if we don't have one
		auto wheel = Cast<ASpringWheel>(spawnChild->GetSpawnedActor());	//if we have one, get the wheel we spawned through the getter
		if (!wheel) { continue; }										//no wheel? skip
		returnArray.Add(wheel);											//add if we have a wheel
	}
	return returnArray;
}
