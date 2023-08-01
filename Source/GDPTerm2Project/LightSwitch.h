// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class GDPTERM2PROJECT_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	UPROPERTY(VisibleAnywhere, Category="Switch Component") // add point light component
	class UPointLightComponent* PointLight1;

	UPROPERTY(VisibleAnywhere, Category="Switch Component") // add sphere collision box for overlaps
	class USphereComponent* Sphere1;

	UPROPERTY(VisibleAnywhere, Category="Switch Variables") //Light intensity
	float DesiredIntensity;

	UFUNCTION() // Overlap begins
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() // Overlap ends
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION() // Light switch toggle
	void ToggleLight();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
