// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) //allows the Tank Barrel to appear in the blueprint editor
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 is max downward, +1 is max upward
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float BarrelMaxHeight = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
	float BarrelMinHeight = 0;

	
};
