// Fill out your copyright notice in the Description page of Project Settings.

#include "Scaler.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UScaler::UScaler()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UScaler::BeginPlay()
{
    Super::BeginPlay();
    
    // Ensure the owning actor's root component has mobility set to movable.
    if(GetOwner()->GetRootComponent())
    {
        GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
    }

    // Initialize the start scale to the root component's current scale.
    StartScale = GetOwner()->GetRootComponent()->GetComponentScale();
}

// Called every frame
void UScaler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Perform the scaling logic in each tick.
    MasterScale(DeltaTime);
}

// Determines scale behavior
void UScaler::MasterScale(float DeltaTime)
{
    // Update the current scale.
    CurrentScale = GetOwner()->GetRootComponent()->GetComponentScale();

    // Check if the scaling should be continuous.
    if(bContinuousScaling) 
    {
        FContinuousScale(DeltaTime);
    }
    else
    {
        // Determine if the scaling should be in reverse or forward.
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

// Easing function for smooth scaling.
FVector UScaler::SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
    // Apply a cubic easing function for smoother scaling transitions.
    float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
    // Linearly interpolate between the current and target scales using the smoothstep value.
    return FMath::Lerp(Current, Target, SmoothAlpha);
}

// Function for scaling up
void UScaler::FScaleUp(float DeltaTime)
{
    if(!bScaleReverse)
    {
        // Set the target scale for scaling up.
        TargetScale = StartScale + ScaleOffset;
        
        // Calculate the interpolation factor (Alpha).
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);
        
        // Interpolate the scale using smoothstep.
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        
        // Update the actor's scale.
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        // Check if the scaling is complete and switch to scaling down.
        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = true;
            StartScale = TargetScale;
            StartTime = GetWorld()->GetTimeSeconds(); // Reset the start time.
        }
    }
}

// Function for scaling down
void UScaler::FScaleDown(float DeltaTime)
{
    if(bScaleReverse)
    {
        // Set the target scale for scaling down.
        TargetScale = StartScale - ScaleOffset;
        
        // Calculate the interpolation factor (Alpha).
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);
        
        // Interpolate the scale using smoothstep.
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        
        // Update the actor's scale.
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        // Check if the scaling is complete and switch to scaling up.
        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = false;
            StartScale = TargetScale;
            StartTime = GetWorld()->GetTimeSeconds(); // Reset the start time.
        }
    }
}

// Function for continuous scaling
void UScaler::FContinuousScale(float DeltaTime)
{
    // Determine the target scale based on the current scaling direction.
    // If scaling in reverse, subtract the offset; otherwise, add the offset.
    TargetScale = bScaleReverse ? CurrentScale - ScaleOffset : CurrentScale + ScaleOffset;
    
    // Calculate the interpolation factor (Alpha) based on the elapsed time and total scaling time.
    // Clamp ensures Alpha stays within the range [0.0, 1.0].
    float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);

    // Interpolate the scale using the smoothstep easing function for a smoother transition.
    FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);

    // Apply the newly calculated scale to the actor's root component, adjusting its size.
    GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);
}
