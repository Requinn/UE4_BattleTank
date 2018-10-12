// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SpringWheel.h"
#include "SpawnActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API USpawnActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	AActor* GetSpawnedActor() const { return SpawnedActor; }
private:
	UPROPERTY(EditDefaultsOnly, Category = Suspension)
	TSubclassOf<AActor> SpawnClass; //Blueprint field so we can spawn any kind of actor
	UPROPERTY()
	AActor* SpawnedActor = nullptr;
		
	
};
