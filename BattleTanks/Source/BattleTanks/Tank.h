// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEvent);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	ATank();
	virtual float TakeDamage(float damage, FDamageEvent const &damageEvent, AController* instigator, AActor* damageSource) override;
	UFUNCTION(BlueprintPure, Category = Tank)
	float GetHealthPercent() const;
	
	FOnDeathEvent OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = Stats)
	int32 Health = 100;
	int32 MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = Suspension)
	UStaticMeshComponent* SuspensionRoot = nullptr;
};
