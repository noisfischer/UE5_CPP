#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ExplodingBarrelComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GDPTERM2PROJECT_API UExplodingBarrelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExplodingBarrelComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* FireParticleSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	URadialForceComponent* RadialForce;

	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle CountdownTimerHandle;

	void Countdown();
};
