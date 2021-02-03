// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooter.h"
#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"




APlayerShooter::APlayerShooter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	CameraComponent->SetupAttachment(RootComponent);

}

void APlayerShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShooter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShooter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerShooter::LookUp);
	PlayerInputComponent->BindAction("Fire", IE_Pressed,this , &APlayerShooter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released,this , &APlayerShooter::EndFire);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &APlayerShooter::SwitchWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerShooter::ReloadWeapon);
}

void APlayerShooter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerShooter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayerShooter::LookUp(float Value)
{
	CameraComponent->AddRelativeRotation(FRotator(Value, 0, 0));
}

void APlayerShooter::BeginPlay()
{
	Super::BeginPlay();


	GetMesh()->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void APlayerShooter::Tick(float DeltaTime)
{
	RecoolDrop(DeltaTime);
}

void APlayerShooter::StartFire()
{
	if (IsReload || IsInEquip()) {
		return;
	}

	GetCurrentWeapon()->StartFire();
}

void APlayerShooter::EndFire()
{
	GetCurrentWeapon()->EndFire();
}

void APlayerShooter::OnDie()
{
	FVector DeltaLocation = FVector(-400, 0, 0);
	CameraComponent->AddLocalOffset(DeltaLocation);
	GetMesh()->SetSkeletalMesh(DeathMesh);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

bool APlayerShooter::IsInEquip()
{
	float Timer = GetWorld()->GetTimeSeconds() - EquipTime;
	return Timer < EquipTimeLength;
}

void APlayerShooter::OnShootOnce()
{
	float Recoil = 2.0f;
	float MaxRecoil = 10.0f;

	float TargetCurrentRecoil = UKismetMathLibrary::FMin(CurrentRecoil + Recoil, MaxRecoil);

	CameraComponent->AddRelativeRotation(FRotator(TargetCurrentRecoil - CurrentRecoil, 0, 0));

	CurrentRecoil = TargetCurrentRecoil;
}

void APlayerShooter::SwitchWeapon()
{
	if (!IsInEquip())
	{
		IsReload = false;
		GetCurrentWeapon()->EndFire();
		GetCurrentWeapon()->SetActorHiddenInGame(true);

		CurrentIndex = (CurrentIndex + 1) % Weapons.Num();

		GetCurrentWeapon()->SetActorHiddenInGame(false);
		PlayAnimMontage(EquipMontage);

		EquipTime = GetWorld()->GetTimeSeconds();

		GetCurrentWeapon()->BulletUpdate();

		OnChangeWeapon.Broadcast(GetCurrentWeapon()->GetIcon());
		///////
	}
}

void APlayerShooter::ReloadWeapon()
{
	if (IsReload || IsInEquip() || GetCurrentWeapon()->IsMaxBullet()) {
		return;
	}

	IsReload = true;
	GetCurrentWeapon()->EndFire();
	CurrentRecoil = 0;

	PlayAnimMontage(GetCurrentWeapon()->GetReloadAnim());
}

void APlayerShooter::RecoolDrop(float Time)
{
	if (CurrentRecoil > 0)
	{
		float RecoilDropSpeed = 2.0f;
		float RecoilDrop = UKismetMathLibrary::FInterpTo_Constant(CurrentRecoil, 0.0f, Time, RecoilDropSpeed);

		CameraComponent->AddRelativeRotation(FRotator(RecoilDrop - CurrentRecoil, 0.0f, 0.0f));

		CurrentRecoil = RecoilDrop;
	}
}

