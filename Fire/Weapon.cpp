// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Shooter.h"
#include "PlayerShooter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

DEFINE_LOG_CATEGORY(LogWeapon);

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	Muzzle = CreateDefaultSubobject<UArrowComponent>("Muzzle");

	RootComponent = SkeletalMesh;
	Muzzle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(FireMontage);
}

void AWeapon::EndFire()
{
	if (BulletNum <= 0)
	{
		if (auto Player = Cast<APlayerShooter>(WeaponOwner))
		{
			Player->ReloadWeapon();
			UE_LOG(LogWeapon, Log, TEXT("Auto Reload"));
		}
	}
}

void AWeapon::Reload()
{
	BulletNum = GetClass()->GetDefaultObject<AWeapon>()->ClipSize;

	BulletUpdate();
	UE_LOG(LogWeapon, Log, TEXT("Reload"));
}

void AWeapon::ShootOnce()
{
	BulletUpdate();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponSound, GetActorLocation());
	if (auto Player = Cast<APlayerShooter>(WeaponOwner))
	{
		Player->OnShootOnce();
	}
}

void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BulletNum = ClipSize;
}

void AWeapon::BulletUpdate()
{
	OnUpdateBullet.Broadcast(BulletNum, ClipSize);
}

