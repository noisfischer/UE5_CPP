#include "ExplodingBarrelComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UExplodingBarrelComponent::UExplodingBarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initial values for the barrel's properties.
	HitPoints = 10.0f;
	ExplosionDamage = 5.0f;
	ExplosionRadius = 20.0f;

	// Initialize and configure the fire particle system component
	FireParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystemComponent"));
	FireParticleSystemComponent->bAutoActivate = false;

	// Initialize and configure the radial force component.
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->Radius = ExplosionRadius;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->bIgnoreOwningActor = false;
}

// Called when the game starts or when spawned.
void UExplodingBarrelComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		// Register the OnDamageTaken function to respond when the actor takes any damage.
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UExplodingBarrelComponent::OnDamageTaken);
	}
}

void UExplodingBarrelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Handler for when the barrel takes damage.
void UExplodingBarrelComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage > 0.f && HitPoints > 0.f)
	{
		// Decrease hit points by the damage amount.
		HitPoints -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Damage taken, Hitpoints: %f"), HitPoints);

		// Activate the fire particle system.
		if (FireParticleSystemComponent != nullptr)
		{
			FireParticleSystemComponent->Activate();
		}

		// Start a countdown timer if it's not already active.
		if (!GetWorld()->GetTimerManager().IsTimerActive(CountdownTimerHandle))
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting countdown timer"));
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UExplodingBarrelComponent::Countdown, 1.0f, true);
		}
	}

	// Check if the barrel's hit points have dropped to zero and it hasn't been destroyed yet.
	if (HitPoints <= 0.f && !bHasBeenDestroyed)
	{
		bHasBeenDestroyed = true;
		
		// Deactivate the fire particle system.
		if (FireParticleSystemComponent != nullptr)
		{
			FireParticleSystemComponent->Deactivate();
		}

		// Apply radial damage and effects.
		FVector BarrelLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::ApplyRadialDamage(GetOwner(), ExplosionDamage, BarrelLocation, ExplosionRadius, nullptr, TArray<AActor*>(), GetOwner());

		// Trigger radial force impulse.
		if (RadialForce)
		{
			RadialForce->FireImpulse();
		}

		// Spawn explosion effects.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, BarrelLocation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, BarrelLocation);

		// I don't want to use this for my game's specific respawn system
		/*  GetOwner()->Destroy();  */
		
		// Set actor to be invisible and have no collisions
		GetOwner()->SetActorHiddenInGame(true);
        GetOwner()->SetActorEnableCollision(false);
	}
}

// Countdown function, reducing hit points over time.
void UExplodingBarrelComponent::Countdown()
{
	HitPoints--;
	UE_LOG(LogTemp, Warning, TEXT("Countdown Called, Hitpoints: %f"), HitPoints);

	if (HitPoints <= 0.f)
	{
		OnDamageTaken(GetOwner(), 0.0f, nullptr, nullptr, nullptr);
	}
}
