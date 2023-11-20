// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EaseMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDPTERM2PROJECT_API UEaseMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEaseMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector StartLocation; // Starting location of the component.
	FVector TargetLocation; // Target location to move to.
	FVector CurrentLocation; // Current location of the component.
	
	// Movement properties
	UPROPERTY(EditAnywhere, Category = "Move")
	float StartTime = 0.0f; // When movement should start
	
	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveTime = 1.0f; // Duration from start to end point of move offset
	
	UPROPERTY(EditAnywhere, Category="Move")
	FVector MoveOffset; // Distance actor should move
	
	UPROPERTY(EditAnywhere, Category="Move")
	bool BMoveReverse = false; // Flag for reversing the movement.

	UPROPERTY(EditAnywhere, Category="Move")
	bool BContinuousMovement = false; // Flag for continuous movement.
	
	// Internal functions for movement logic.
	FVector SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha); // Function for smoothstep interpolation.
	void MasterMove(float DeltaTime); // Master movement function.
	void FMoveReverse(float DeltaTime); // Function to handle reverse movement.
	void FMoveForward(float DeltaTime); // Function to handle forward movement.
	void FContinuousMove(float DeltaTime); // Function to handle continuous movement.
	
};
