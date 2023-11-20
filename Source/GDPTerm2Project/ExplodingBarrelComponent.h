#pragma once

#include "CoreMinimal.h" // Core functionalities.
#include "Components/ActorComponent.h" // Base class for actor components.
#include "Sound/SoundCue.h" // For sound cue functionalities.
#include "PhysicsEngine/RadialForceComponent.h" // For radial force physics.
#include "Particles/ParticleSystemComponent.h" // For particle system components.
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
	UStaticMeshComponent* BarrelMesh; //static mesh component of exploding barrel

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float HitPoints; //health of component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float ExplosionDamage; //radial damage dealt

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	float ExplosionRadius; // area of effect of explosion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploding Barrel")
	USoundCue* ExplosionSound; //modifiable explosion sound

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ExplosionParticle; //modifiable explosion effect

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* FireParticleSystemComponent; //modifiable fire particle effect

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	URadialForceComponent* RadialForce; //for physics interactions like enemy ragdoll on death

	// BlueprintCallable function to handle damage taken by the barrel.
	UFUNCTION(BlueprintCallable)
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Explosion timer countdown when barrel is slightly damaged
	FTimerHandle CountdownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destroyed")
	bool bHasBeenDestroyed = false; //Check if actor with explosive component has been destroyed

	// Function for countdown behavior.
	void Countdown();
};
