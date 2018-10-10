// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "SpringWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(SpringComponent);

	WheelComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	WheelComponent->SetupAttachment(SpringComponent);
}

void ASpringWheel::SetUpConstraints() {
	if (GetAttachParentActor()) {
		UPrimitiveComponent* Body = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (Body) {
			SpringComponent->SetConstrainedComponents(Body, NAME_None, WheelComponent, NAME_None); //just setting the constrained objects of the PhysicsConstraintComponent
		}
	}
}
// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	SetUpConstraints();
}

// Called every frame
void ASpringWheel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}