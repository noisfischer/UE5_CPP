// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDPTERM2PROJECT_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	// Define variables and functions for move
	FVector StartLocation;
	FVector TargetLocation;
	FVector CurrentLocation;
	
	UPROPERTY(EditAnywhere, Category="Move")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category="Move", meta=(ClampMin="0", ClampMax="1000", UIMin="0", UIMax="1000"))
	float MoveTime = 1.0f;
	UPROPERTY(EditAnywhere, Category="Move")
	bool BMoveReverse = false;
	UPROPERTY(EditAnywhere, Category="Move")
	bool BContinuousMovement = false;
	
	void MasterMove(float DeltaTime);
	void FMoveReverse(float DeltaTime);
	void FMoveForward(float DeltaTime);
	void FContinuousMove(float DeltaTime);
};
