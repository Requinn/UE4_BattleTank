// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankController.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComponent){
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NO AIM COMPONENT FOUND"));
	}
}

void ATankController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	FVector HitLocation; //out param
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
	//get world location through a linecast through the point on the screen
	//if the line cast hits the world, aim towards that point
}

//return if we hit something, assigning the reference HitLocation parameter(out param)
bool ATankController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	//linetrace to a point
	//assign Hitlocation
	//return true if assigned
	
	//viewport size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//get the location of our crosshair on the screen
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairX, ViewportSizeY * CrossHairY);
	FVector CameraLookDirection;
	//get the direction we are looking at by deprojecting our screen point to the world
	if (GetLookDirection(ScreenLocation, CameraLookDirection)) {
		//use the CamaeraLookDirection OUT param as a input to tell the direction of our linetrace
		GetLookVectorHitLocation(CameraLookDirection, OutHitLocation);
	}
	
	return true;
	
}

//Get the direcion we are looking at into the OUT param 
bool ATankController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector OutCameraWorldLocation; //for discarding
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutCameraWorldLocation, LookDirection);
}

//Given a direction, get the position OUT param of where we are looking at
bool ATankController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto lookOrigin = PlayerCameraManager->GetCameraLocation(); //get the origin point, which is our camera
	FVector EndLocation = lookOrigin + (LookDirection * LineTraceRange); //calculate the end position of our line trace

	//do the linetrace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, lookOrigin, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location; //if we hit something, set our OUT param to the locatoin we hit
		return true;
	}
	else {
		HitLocation = FVector(0); //if we didn't hit something, use a zero vector
		return false;
	}
}