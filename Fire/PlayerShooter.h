// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "PlayerShooter.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeWeaponDelegate, UTexture2D*, Icon);


class USkeletalMesh;

UCLASS()
class FIRE_API APlayerShooter : public AShooter
{
	GENERATED_BODY()

public:
	APlayerShooter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void StartFire();
	void EndFire();

	FVector GetShootLocation() override { return CameraComponent->GetComponentLocation(); }
	FVector GetShootDirection() override { return CameraComponent->GetForwardVector(); }

	void OnDie();

	bool IsInEquip();

	void OnShootOnce();

	UPROPERTY(BlueprintAssignable)
	FChangeWeaponDelegate OnChangeWeapon;

	void ReloadWeapon();

protected:
	void SwitchWeapon();

	void RecoolDrop(float Time);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category ="PlayerShooter")
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PlayerShooter")
	USkeletalMesh* DeathMesh;

	float EquipTime;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PlayerShooter")
	class UAnimMontage* EquipMontage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PlayerShooter")
	float EquipTimeLength = 0.3f;

};
