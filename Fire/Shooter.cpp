// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "TimerManager.h"
#include "ShooterGameInstance.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
	InitWeapons();
	OnUpdateHealth.Broadcast(GetHealth(), GetMaxHealth());
}


// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooter::Destroyed()
{
	for (auto Weapon : Weapons)
	{
		Weapon->Destroy();
	}
}

void AShooter::TakeWeaponDamage(float Damage, AShooter* Enemy)
{
	if (IsDead()) {
		return;
	}
	Health -= Damage;

	OnUpdateHealth.Broadcast(GetHealth(), GetMaxHealth());

	UE_LOG(LogTemp, Log, TEXT("Health : %f"), GetHealth());

	if (IsDead()) 
	{
		Die(Enemy);
	}
}

void AShooter::InitWeapons()
{
	check(WeaponClasses.Num() > 0);
	for (auto WeaponClass : WeaponClasses)
	{
		CreateWeapon(WeaponClass);
	}
	Weapons[0]->SetActorHiddenInGame(false);

}

void AShooter::CreateWeapon(TSubclassOf<AWeapon> WeaponClass)
{
	FActorSpawnParameters Params;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass,Params);

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(GetMesh(), Rules, "b_RightRifleSocket");

	Weapon->SetWeaponOwner(this);
	Weapons.Add(Weapon);
	Weapon->SetActorHiddenInGame(true);
}

void AShooter::Die(AShooter* Enemy)
{
	for (auto Weapon : Weapons)
	{
		Weapon->EndFire();
	}
	OnDie();
	
	UShooterGameInstance* GameInstance = Cast<UShooterGameInstance>(GetGameInstance());
	GameInstance->OnKillInfoUpdate.Broadcast(Enemy->GetName(), this->GetName(), Enemy->Team, this->Team,Enemy->GetCurrentWeapon()->GetIcon());
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &APawn::DetachFromControllerPendingDestroy, 0.1f, false);
}

void AShooter::OnDie()
{
}


