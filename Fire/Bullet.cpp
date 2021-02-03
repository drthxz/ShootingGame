// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Shooter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	RootComponent = SphereCollision;
	MeshComponent->SetupAttachment(RootComponent);

	SphereCollision->SetSphereRadius(5.0f);
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll"));

	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));

	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto Enemy = Cast<AShooter>(OtherActor))
	{
		Enemy->TakeWeaponDamage(50.0f, Shooter);
		Destroy();
	}
}

