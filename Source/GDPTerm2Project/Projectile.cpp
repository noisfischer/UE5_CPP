// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the Projectile Mesh and set it as the Root Component.
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	// Initialize the Projectile Movement Component with specific properties.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f; // Set the initial speed of the projectile.
	ProjectileMovementComponent->MaxSpeed = 3000.0f; // Set the maximum speed of the projectile.
	ProjectileMovementComponent->bRotationFollowsVelocity = true; // The projectile's rotation will follow its velocity.
	ProjectileMovementComponent->bShouldBounce = false; // The projectile will not bounce upon impact.
	
	// Set the damage the projectile can inflict.
	Damage = 5;

}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// NotifyHit is called when the projectile hits something.
void AProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit); // Call base class's NotifyHit

	if(Other != nullptr)
	{
		// Apply damage to the hit actor.
		UGameplayStatics::ApplyPointDamage(Other, Damage, GetActorLocation() - Other->GetActorLocation(), Hit, nullptr, this, nullptr);
	}

	// Destroy the projectile after it hits something.
	Destroy();
}

