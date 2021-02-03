// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter.h"
#include "RobotShooter.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API ARobotShooter : public AShooter
{
	GENERATED_BODY()
	
public:
	FVector GetShootLocation() { return this->GetActorLocation(); }
	FVector GetShootDirection() { return this->GetActorForwardVector(); }
};
