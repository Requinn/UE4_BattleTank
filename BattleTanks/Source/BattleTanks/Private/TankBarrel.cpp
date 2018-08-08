// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	auto Time = GetWorld()->GetTimeSeconds(); //get elapsed time in seconds
	UE_LOG(LogTemp, Warning, TEXT("DPS %f"), RelativeSpeed);
}



