// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

UCLASS()
class BATTLETANKS_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void AddDrivingForce(float forceMagnitude);

private:
	void SetUpConstraints();
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* SpringComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* AxleJoint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* WheelComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* AxleComponent = nullptr;

	float totalDriveForce = 0.0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
