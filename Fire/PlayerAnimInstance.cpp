// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Shooter.h"


void UPlayerAnimInstance::AnimNotify_ReloadOver(UAnimNotify* Notify)
{
	auto WeaponOwner = Cast<AShooter>(TryGetPawnOwner());

	WeaponOwner->GetCurrentWeapon()->Reload();

	WeaponOwner->SetIsReload(false);
}