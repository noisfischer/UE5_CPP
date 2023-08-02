// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// Set owner actor to Movable on begin play
	if(GetOwner()->GetRootComponent())
	{
		GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	}
	
	// Start Location and Rotation of owner actor on BeginPlay
	StartLocation = GetOwner()->GetActorLocation();
	StartRotation = GetOwner()->GetActorRotation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MasterMove(DeltaTime);
	MasterRotate(DeltaTime);
}


// MASTER MOVE FUNCTION
void UMover::MasterMove(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();

	if(BContinuousMovement == true)
	{
		FContinuousMove(DeltaTime);
	}
	else
	{
		if(BMoveReverse == true)
		{
			FMoveReverse(DeltaTime);
		}
		else
		{
			FMoveForward(DeltaTime);
		}
	}
}


// MASTER ROTATE FUNCTION
void UMover::MasterRotate(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();

	if(BContinuousRotation == true)
	{
		FContinuousRotate(DeltaTime);
	}
	else
	{
		if(BRotateReverse == true)
		{
			FRotateReverse(DeltaTime);
		}
		else
		{
			FRotateForward(DeltaTime);
		}
	}
}

// Function for continuous movement
void UMover::FContinuousMove(float DeltaTime)
{
	TargetLocation = BMoveReverse ? CurrentLocation - MoveOffset : CurrentLocation + MoveOffset;
	float MoveSpeed = FVector::Distance(CurrentLocation, TargetLocation) / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);
}

// Function for forward movement
void UMover::FMoveForward(float DeltaTime)
{
	if(BMoveReverse == false)
	{
		// Forward Movement
		TargetLocation = StartLocation + MoveOffset;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, (1.0f / MoveTime) * 1000);
		GetOwner()->SetActorLocation(NewLocation);

		if(FVector::Distance(CurrentLocation, TargetLocation) <= SMALL_NUMBER)
		{
			BMoveReverse = true;
			StartLocation = TargetLocation;
		}
	}
}

// Function for reverse movement
void UMover::FMoveReverse(float DeltaTime)
{
	if(BMoveReverse == true)
	{
		// Reverse Movement
		TargetLocation = StartLocation - MoveOffset;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, (1.0f / MoveTime) * 1000);
		GetOwner()->SetActorLocation(NewLocation);

		if(FVector::Distance(CurrentLocation, TargetLocation) <= SMALL_NUMBER)
		{
			BMoveReverse = false;
			StartLocation = TargetLocation;
		}
	}
}


// Function for forward rotation
void UMover::FRotateForward(float DeltaTime)
{
	if(BRotateReverse == false)
	{
		TargetRotation = StartRotation + RotateOffset;
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, (1.0f / RotationTime) * 1000);
		GetOwner()->SetActorRotation(NewRotation);

		if(FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= SMALL_NUMBER)
		{
			BRotateReverse = true;
			StartRotation = TargetRotation;
		}
	}
}

// Function for reverse rotation
void UMover::FRotateReverse(float DeltaTime)
{
	if(BRotateReverse == true)
	{
		TargetRotation = StartRotation - RotateOffset;
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, (1.0f / RotationTime) * 1000);
		GetOwner()->SetActorRotation(NewRotation);

		if(FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= SMALL_NUMBER)
		{
			BRotateReverse = false;
			StartRotation = TargetRotation;
		}
	}
}


// Function for continuous rotation
void UMover::FContinuousRotate(float DeltaTime)
{
	if(BRotateReverse == false)
	{
		TargetRotation = CurrentRotation + RotateOffset;
	}

	else
	{
		TargetRotation = CurrentRotation - RotateOffset;
	}
		
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, (1.0f / RotationTime) * 1000);
	GetOwner()->SetActorRotation(NewRotation);
}




