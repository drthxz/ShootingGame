// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"  
#include "Animation/AnimMontage.h"
#include "Weapon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateBulletDelegate, int, BulletNum, int, ClipSize);


class USkeletalMeshComponent;
class UArrowComponent;
class AShooter;
class UParticleSystem;
class UAnimMontage;

UCLASS()
class FIRE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void SetWeaponOwner(AShooter* Shooter) { WeaponOwner = Shooter; }

	virtual void StartFire() {};
	virtual void EndFire();

	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void ShootOnce();

	virtual void PostInitializeComponents() override;

	UAnimMontage* GetReloadAnim() { return ReloadMontage; }

	UTexture2D* GetIcon() { return Icon; }

	bool IsMaxBullet() { return BulletNum == ClipSize; }

	virtual void BulletUpdate();

	UPROPERTY(BlueprintAssignable)
	FUpdateBulletDelegate OnUpdateBullet;

	UFUNCTION(BlueprintPure, Category = "Weapon")
	float GetMoveSpeed() { return 400.0f; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon")
	UArrowComponent* Muzzle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* FireMontage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* FireEffectPath;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;

	AShooter* WeaponOwner;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	int ClipSize;
	int BulletNum;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	class USoundBase* WeaponSound;
};
