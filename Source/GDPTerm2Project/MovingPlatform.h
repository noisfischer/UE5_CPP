// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class GDPTERM2PROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	// sets as static mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MovingPlatformMesh; 
	
	// Numbers practice
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	int32 InputAInt = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	float InputBFloat = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	float MyNewNumber = 0.0f;

	// Vector Practice
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	FVector MyVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	float MyX = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	FVector PlatformVelocity = FVector(100, 0, 0);

	FVector StartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Moving Platform")
	float DistanceMoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Platform")
	float MaxMoveDistance = 100.0f;

};
