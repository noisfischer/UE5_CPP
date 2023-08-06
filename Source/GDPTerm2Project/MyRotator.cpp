// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRotator.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMyRotator::UMyRotator()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMyRotator::BeginPlay()
{
	Super::BeginPlay();

	// Set owner actor to Movable on begin play
	if(GetOwner()->GetRootComponent())
	{
		GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	}
	
	// Start Rotation of owner actor on BeginPlay
	StartRotation = GetOwner()->GetActorRotation();
	
}


// Called every frame
void UMyRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	MasterRotate(DeltaTime);
}



// MASTER ROTATE FUNCTION
void UMyRotator::MasterRotate(float DeltaTime)
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


// Function for forward rotation
void UMyRotator::FRotateForward(float DeltaTime)
{
	if(BRotateReverse == false)
	{
		TargetRotation = StartRotation + RotateOffset;
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, (1.0f / RotationTime) * 1000);
		GetOwner()->SetActorRotation(NewRotation);

		if(FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
		{
			BRotateReverse = true;
			StartRotation = TargetRotation;
		}
	}
}

// Function for reverse rotation
void UMyRotator::FRotateReverse(float DeltaTime)
{
	if(BRotateReverse == true)
	{
		TargetRotation = StartRotation - RotateOffset;
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, (1.0f / RotationTime) * 1000);
		GetOwner()->SetActorRotation(NewRotation);

		if(FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
		{
			BRotateReverse = false;
			StartRotation = TargetRotation;
		}
	}
}


// Function for continuous rotation
void UMyRotator::FContinuousRotate(float DeltaTime)
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






