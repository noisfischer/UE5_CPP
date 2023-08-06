// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MasterTransform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDPTERM2PROJECT_API UMasterTransform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMasterTransform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// MOVER FUNCTIONS AND VARIABLES
	FVector StartLocation;
	FVector TargetLocation;
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveStartTime = 0.0f; // The time the movement started
	
	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveTime = 1.0f; // The total time the movement should take
	
	UPROPERTY(EditAnywhere, Category="Move")
	FVector MoveOffset;
	
	UPROPERTY(EditAnywhere, Category="Move")
	bool BMoveReverse = false;

	UPROPERTY(EditAnywhere, Category="Move")
	bool BContinuousMovement = false;

	FVector SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha); // Function for ease motion
	void MasterMove(float DeltaTime);
	void FMoveReverse(float DeltaTime);
	void FMoveForward(float DeltaTime);
	void FContinuousMove(float DeltaTime);

	
	// ROTATOR FUNCTIONS AND VARIABLES
	FRotator StartRotation;
	FRotator CurrentRotation;
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, Category="Rotate", meta=(ClampMin="0", ClampMax="20", UIMin="0", UIMax="20"))
	float RotationTime = 5.0f;  // default value

	UPROPERTY(EditAnywhere, Category="Rotate")
	FRotator RotateOffset;

	// Current elapsed time since rotation started
	float RotateCurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BRotateReverse;

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BContinuousRotation;
	void MasterRotate(float DeltaTime);
	void FRotateForward(float DeltaTime);
	void FRotateReverse(float DeltaTime);
	void FContinuousRotate(float DeltaTime);
	void ApplyRotation(float DeltaTime);
	float CubicEaseInOut(float t);

	
	// SCALE FUNCTIONS AND VARIABLES
	FVector StartScale;
	FVector TargetScale;
	FVector CurrentScale;

	void MasterScale(float DeltaTime);
	FVector ScaleSmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha);
	void FScaleUp(float DeltaTime);
	void FScaleDown(float DeltaTime);
	void FContinuousScale(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Scaling")
	FVector ScaleOffset;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	float ScaleTime;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bScaleReverse;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bContinuousScaling;

	float ScaleStartTime;
};
