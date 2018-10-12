// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "SpringWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

///DON'T FORGET TO MAKE SURE YOUR MESHES FOR WHEELS AND SHIT HAVE COLLIDERS ON THEM

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SpringComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(SpringComponent);

	AxleComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	AxleComponent->SetupAttachment(SpringComponent);

	WheelComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	WheelComponent->SetupAttachment(AxleComponent);

	AxleJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleJoint"));
	AxleJoint->SetupAttachment(AxleComponent);

}

void ASpringWheel::SetUpConstraints() {
	if (GetAttachParentActor()) {
		UPrimitiveComponent* Body = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (Body) {
			SpringComponent->SetConstrainedComponents(Body, NAME_None, AxleComponent, NAME_None); //just setting the constrained objects of the PhysicsConstraintComponent
			AxleJoint->SetConstrainedComponents(AxleComponent, NAME_None, WheelComponent, NAME_None);
		}
	}
}

void ASpringWheel::AddDrivingForce(float forceMagnitude) {
	totalDriveForce += forceMagnitude; //adding forces from both of the wheels
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	SetUpConstraints();
	WheelComponent->OnComponentHit.AddDynamic(this, &ASpringWheel::OnHit);
}

// Called every frame
void ASpringWheel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//Check if we're in the right tickgroup
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		totalDriveForce = 0;
	}
}

void ASpringWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	WheelComponent->AddForce(totalDriveForce * AxleComponent->GetForwardVector());
}