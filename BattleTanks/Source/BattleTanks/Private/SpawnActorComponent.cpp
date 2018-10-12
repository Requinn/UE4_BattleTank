// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "SpawnActorComponent.h"


// Sets default values for this component's properties
USpawnActorComponent::USpawnActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpawnActorComponent::BeginPlay()
{
	Super::BeginPlay();
	//Because we might have a race condition of us spawning this actor, then having the actor find the parent before this sets its own parent
	//we use SpawnActorDeferred to hold off on "finalized" creation before we are done through FinishSpawnginActor
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	// ...
	
}

