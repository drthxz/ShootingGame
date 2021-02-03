// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "Components/ArrowComponent.h"
#include "Shooter.h"
#include "Bullet.h"
#include "PlayerShooter.h"

DEFINE_LOG_CATEGORY(LogProjectileWeapon);

AProjectileWeapon::AProjectileWeapon()
{
	
}

void AProjectileWeapon::StartFire()
{
	ShootOnce();
}

void AProjectileWeapon::ShootOnce()
{
	if (BulletNum <= 0) {
		EndFire();
		return;
	}
	float Timer = GetWorld()->GetTimeSeconds() - LastShootTime;
	
	if (Timer >= ShootAnimTimeLength)
	{
		BulletNum--;

		Super::ShootOnce();
		
		auto Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, Muzzle->GetComponentLocation(), WeaponOwner->GetControlRotation());
		Bullet->Shooter = WeaponOwner;

		WeaponOwner->PlayAnimMontage(FireMontage);

		LastShootTime = GetWorld()->GetTimeSeconds();

		UE_LOG(LogProjectileWeapon, Log, TEXT("Shoot Once !"));
	}
}

