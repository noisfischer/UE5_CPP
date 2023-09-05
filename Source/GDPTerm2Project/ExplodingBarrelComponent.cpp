#include "ExplodingBarrelComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UExplodingBarrelComponent::UExplodingBarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	HitPoints = 10.0f;
	ExplosionDamage = 5.0f;
	ExplosionRadius = 20.0f;

	FireParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystemComponent"));
	FireParticleSystemComponent->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->Radius = ExplosionRadius;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->bIgnoreOwningActor = false;
}

void UExplodingBarrelComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UExplodingBarrelComponent::OnDamageTaken);
	}
}

void UExplodingBarrelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UExplodingBarrelComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage > 0.f && HitPoints > 0.f)
	{
		HitPoints -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Damage taken, Hitpoints: %f"), HitPoints);

		if (FireParticleSystemComponent != nullptr)
		{
			FireParticleSystemComponent->Activate();
		}

		if (!GetWorld()->GetTimerManager().IsTimerActive(CountdownTimerHandle))
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting countdown timer"));
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UExplodingBarrelComponent::Countdown, 1.0f, true);
		}
	}

	if (HitPoints <= 0.f)
	{
		if (FireParticleSystemComponent != nullptr)
		{
			FireParticleSystemComponent->Deactivate();
		}

		FVector BarrelLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::ApplyRadialDamage(GetOwner(), ExplosionDamage, BarrelLocation, ExplosionRadius, nullptr, TArray<AActor*>(), GetOwner());

		if (RadialForce)
		{
			RadialForce->FireImpulse();
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, BarrelLocation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, BarrelLocation);

		GetOwner()->Destroy();
	}
}

void UExplodingBarrelComponent::Countdown()
{
	HitPoints--;
	UE_LOG(LogTemp, Warning, TEXT("Countdown Called, Hitpoints: %f"), HitPoints);

	if (HitPoints <= 0.f)
	{
		OnDamageTaken(GetOwner(), 0.0f, nullptr, nullptr, nullptr);
	}
}
