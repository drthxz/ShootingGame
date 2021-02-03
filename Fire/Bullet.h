// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"


class AShooter;
class UProjectileMovementComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FIRE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn =true) , Category = "Bullet")
	AShooter* Shooter;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Bullet")
	USphereComponent* SphereCollision;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Bullet")
	UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
