// Fill out your copyright notice in the Description page of Project Settings.
#include "IDamageable.generated.h"
#pragma once

///TODO: Maybe Convert the damage done to tanks into something done through IDamageable?
UINTERFACE()
class UDamageable : public UInterface {
	GENERATED_BODY()
};

class IDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void HandleDeath();
};

