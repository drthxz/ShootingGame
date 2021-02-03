// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"

/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(LogProjectileWeapon, Log, All);

class ABullet;

UCLASS()
class FIRE_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	void StartFire() override;
	void ShootOnce() override;

protected:
	AProjectileWeapon();


protected:
	float LastShootTime;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category = "Weapon")
	float ShootAnimTimeLength;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ABullet> BulletClass;
};
