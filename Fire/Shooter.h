// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Shooter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateHealthDelegate, float, Health, float, MaxHealth);

UCLASS()
class FIRE_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

	UPROPERTY(BlueprintAssignable)
	FUpdateHealthDelegate OnUpdateHealth;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsReload;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	UFUNCTION(BlueprintPure, Category = "Shooter")
	AWeapon* GetCurrentWeapon() { return Weapons[CurrentIndex]; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
	TArray<AWeapon*> GetWeapons() { return Weapons; }

	virtual FVector GetShootLocation() { return FVector::ZeroVector; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
		virtual FVector GetShootDirection() { return FVector::ZeroVector; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
		bool IsDead() { return Health <= 0; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
		bool IsEnemy(AShooter* Another) { check(Another != nullptr); return Team != Another->Team; }

	void TakeWeaponDamage(float Damage, AShooter* Enemy);

	void SetIsReload(bool InReload) { IsReload = InReload; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
	float GetHealth() { return Health; }

	UFUNCTION(BlueprintPure, Category = "Shooter")
	float GetMaxHealth() { return GetClass()->GetDefaultObject<AShooter>()->Health; }

	UFUNCTION(BlueprintPure, Category = "PlayerShooter")
	float GetCurrentRecoil() { return CurrentRecoil; }

protected:
	void InitWeapons();
	void CreateWeapon(TSubclassOf<AWeapon> WeaponClass);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Shooter")
	TArray<TSubclassOf<AWeapon>> WeaponClasses;

	TArray<AWeapon*> Weapons;

	int CurrentIndex;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shooter")
	float Health;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shooter")
	int Team;

	float ReloadTime;

	float CurrentRecoil;

private:
	void Die(AShooter* Enemy);

	void OnDie();
};
