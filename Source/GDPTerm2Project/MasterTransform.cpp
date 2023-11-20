// Incorporates scripts from EaseMover, MyRotator, and Scaler

#include "MasterTransform.h"

// Sets default values for this component's properties
UMasterTransform::UMasterTransform()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMasterTransform::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->GetRootComponent())
	{
		GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	}
	StartLocation = GetOwner()->GetActorLocation();
	StartScale = GetOwner()->GetRootComponent()->GetComponentScale();
	StartRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UMasterTransform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MasterMove(DeltaTime);
	MasterScale(DeltaTime);
	MasterRotate(DeltaTime);
}

// Master Move Function
void UMasterTransform::MasterMove(float DeltaTime)
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

// Function for ease movement
FVector UMasterTransform::SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
	float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
	return FMath::Lerp(Current, Target, SmoothAlpha);
}

// Function for forward movement
void UMasterTransform::FMoveForward(float DeltaTime)
{
	if(!BMoveReverse)
	{
		TargetLocation = StartLocation + MoveOffset;
		float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - MoveStartTime) / MoveTime, 0.0f, 1.0f);
		FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
		GetOwner()->SetActorLocation(NewLocation);

		if(FVector::Distance(CurrentLocation, TargetLocation) <= 0.1f)
		{
			BMoveReverse = true;
			StartLocation = TargetLocation;
			MoveStartTime = GetWorld()->GetTimeSeconds(); // Reset the start time for the reverse move
		}
	}
}

// Function for reverse movement
void UMasterTransform::FMoveReverse(float DeltaTime)
{
	if(BMoveReverse)
	{
		TargetLocation = StartLocation - MoveOffset;
		float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - MoveStartTime) / MoveTime, 0.0f, 1.0f);
		FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
		GetOwner()->SetActorLocation(NewLocation);

		if(FVector::Distance(CurrentLocation, TargetLocation) <= 0.1f)
		{
			BMoveReverse = false;
			StartLocation = TargetLocation;
			MoveStartTime = GetWorld()->GetTimeSeconds(); // Reset the start time for the forward move
		}
	}
}


// Function for continuous movement
void UMasterTransform::FContinuousMove(float DeltaTime)
{
	TargetLocation = BMoveReverse ? CurrentLocation - MoveOffset : CurrentLocation + MoveOffset;
	float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - MoveStartTime) / MoveTime, 0.0f, 1.0f);
	FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
	GetOwner()->SetActorLocation(NewLocation);
}



// Master Scale Function
void UMasterTransform::MasterScale(float DeltaTime)
{
    CurrentScale = GetOwner()->GetRootComponent()->GetComponentScale();
    
    if(bContinuousScaling) 
    {
        FContinuousScale(DeltaTime);
    }
    else
    {
        if(bScaleReverse)
        {
            FScaleDown(DeltaTime);
        }
        else
        {
            FScaleUp(DeltaTime);
        }
    }
}

// Function for ease scale
FVector UMasterTransform::ScaleSmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
    float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
    return FMath::Lerp(Current, Target, SmoothAlpha);
}

// Function for scaling up
void UMasterTransform::FScaleUp(float DeltaTime)
{
    if(!bScaleReverse)
    {
        TargetScale = StartScale + ScaleOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - ScaleStartTime) / ScaleTime, 0.0f, 1.0f);
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = true;
            StartScale = TargetScale;
            ScaleStartTime = GetWorld()->GetTimeSeconds();
        }
    }
}

// Function for scaling down
void UMasterTransform::FScaleDown(float DeltaTime)
{
    if(bScaleReverse)
    {
        TargetScale = StartScale - ScaleOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - ScaleStartTime) / ScaleTime, 0.0f, 1.0f);
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = false;
            StartScale = TargetScale;
            ScaleStartTime = GetWorld()->GetTimeSeconds();
        }
    }
}

// Function for continuous scaling
void UMasterTransform::FContinuousScale(float DeltaTime)
{
    TargetScale = bScaleReverse ? CurrentScale - ScaleOffset : CurrentScale + ScaleOffset;
    float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - ScaleStartTime) / ScaleTime, 0.0f, 1.0f);
    FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
    GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);
}



// MASTER ROTATE FUNCTION
void UMasterTransform::MasterRotate(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();

	if (BContinuousRotation)
	{
		FContinuousRotate(DeltaTime);
	}
	else
	{
		if (BRotateReverse)
		{
			FRotateReverse(DeltaTime);
		}
		else
		{
			FRotateForward(DeltaTime);
		}
	}
}

// ApplyRotation
void UMasterTransform::ApplyRotation(float DeltaTime)
{
	RotateCurrentTime += DeltaTime;
	float Alpha = FMath::Clamp(RotateCurrentTime / RotationTime, 0.0f, 1.0f);
	float EasedAlpha = CubicEaseInOut(Alpha);

	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, EasedAlpha);
	GetOwner()->SetActorRotation(NewRotation);
}

// Function for forward rotation
void UMasterTransform::FRotateForward(float DeltaTime)
{
	TargetRotation = StartRotation + RotateOffset;
	ApplyRotation(DeltaTime);

	if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
	{
		BRotateReverse = true;
		StartRotation = TargetRotation;
		RotateCurrentTime = 0.0f; // Resetting the CurrentTime
	}
}

// Function for reverse rotation
void UMasterTransform::FRotateReverse(float DeltaTime)
{
	TargetRotation = StartRotation - RotateOffset;
	ApplyRotation(DeltaTime);

	if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
	{
		BRotateReverse = false;
		StartRotation = TargetRotation;
		RotateCurrentTime = 0.0f; // Resetting the CurrentTime
	}
}

// Function for continuous rotation
void UMasterTransform::FContinuousRotate(float DeltaTime)
{
	TargetRotation = (BRotateReverse) ? CurrentRotation - RotateOffset : CurrentRotation + RotateOffset;
	ApplyRotation(DeltaTime);
}

float UMasterTransform::CubicEaseInOut(float t)
{
	if (t < 0.5f)
	{
		return 4.0f * t * t * t;
	}
	else
	{
		float f = t - 1.0f;
		return 1.0f + 4.0f * f * f * f;
	}
}