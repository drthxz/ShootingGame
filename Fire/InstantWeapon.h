// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "InstantWeapon.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogInstantWeapon, Log, All);


class UParticleSystemComponent;


UCLASS()
class FIRE_API AInstantWeapon : public AWeapon
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AInstantWeapon();
	void StartFire() override;
	void EndFire() override;
	void ShootOnce() override;

protected:
	UParticleSystemComponent* FireEffect;

	bool bIsInFire;

	FTimerHandle TimerHandle;

	
};
