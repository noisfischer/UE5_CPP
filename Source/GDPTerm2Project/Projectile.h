// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS(Blueprintable)
class GDPTERM2PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Static Mesh Component to visually represent the projectile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* ProjectileMesh;

	// Movement Component for handling projectile movement.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Damage property of the projectile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int Damage;

	// Override for NotifyHit to handle behavior when the projectile hits something.
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
