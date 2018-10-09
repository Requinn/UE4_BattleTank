// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTanks.h"
#include "Tank.h"

void ATank::BeginPlay() {
	Super::BeginPlay();
	Health = MaxHealth;
}

float ATank::TakeDamage(float damage, FDamageEvent const & damageEvent, AController * instigator, AActor * damageSource)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(damage);
	Health -= FMath::Clamp(DamagePoints, 0, Health);
	if (Health <= 0) {
		OnDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("%i"), Health);
	return 0.0f;
}

float ATank::GetHealthPercent() const
{
	return (float)Health / (float)MaxHealth;
}
