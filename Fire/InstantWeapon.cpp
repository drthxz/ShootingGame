// Fill out your copyright notice in the Description page of Project Settings.


#include "InstantWeapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Materials/MaterialInterface.h"
#include "Components/DecalComponent.h"
#include "PlayerShooter.h"


DEFINE_LOG_CATEGORY(LogInstantWeapon);

AInstantWeapon::AInstantWeapon()
{
	
}

void AInstantWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(FireMontage);
	check(FireEffectPath);
}

void AInstantWeapon::StartFire()
{
	bIsInFire = true;
	WeaponOwner->PlayAnimMontage(FireMontage);

	FireEffect = UGameplayStatics::SpawnEmitterAttached(FireEffectPath, Muzzle);

	ShootOnce();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AInstantWeapon::ShootOnce, 0.2f, true);
}

void AInstantWeapon::EndFire()
{
	Super::EndFire();

	if (bIsInFire)
	{
		WeaponOwner->StopAnimMontage(FireMontage);
		FireEffect->DestroyComponent();

		GetWorldTimerManager().ClearTimer(TimerHandle);
		bIsInFire = false;

		UE_LOG(LogInstantWeapon, Log, TEXT("EndFire"));
	}
}

void AInstantWeapon::ShootOnce()
{
	if (BulletNum <= 0)
	{
		EndFire();
		
		return;
	}

	BulletNum--;

	Super::ShootOnce();

	FVector Start = WeaponOwner->GetShootLocation();
	//float Riadius = 15.0f;
	//float Range = 2200.0f;
	float CurrentRecoil = (WeaponOwner->GetCurrentRecoil() + 1.0f) / 5.0f;
	float Radians = 15.0f * CurrentRecoil / 2200.0f;

	FVector ShootDirection = UKismetMathLibrary::RandomUnitVectorInConeInRadians(WeaponOwner->GetShootDirection(), Radians);
	FVector End = Start + (UKismetMathLibrary::Normal(ShootDirection)*1500);

	TArray<AActor*> Ignore;
	Ignore.Add(WeaponOwner);

	FHitResult HitResult;
	bool IsHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery2, false, Ignore, EDrawDebugTrace::None, HitResult, true);
	if (!IsHit) {
		return;
	}

	UMaterialInterface* DecalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Assets/Effects/Materials/Weapon/M_Impact_Decal"));
	FVector DecailSize = FVector(10, 10, 10);
	FRotator Rotator = UKismetMathLibrary::Conv_VectorToRotator(HitResult.ImpactNormal); 

	Rotator.Roll = UKismetMathLibrary::RandomFloatInRange(180, -180);

	auto SpawnDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecailSize, HitResult.ImpactPoint, Rotator, 5.f);
	SpawnDecal->SetFadeScreenSize(0.0f);

	AShooter* Enemy = Cast<AShooter>(HitResult.Actor);
	
	if (!Enemy || !WeaponOwner->IsEnemy(Enemy)) {
		return;
	}

	Enemy->TakeWeaponDamage(20.0f, WeaponOwner);

	UE_LOG(LogInstantWeapon, Log, TEXT("Shoot Once !"));
}

