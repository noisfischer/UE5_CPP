// Fill out your copyright notice in the Description page of Project Settings.

#include "EaseMover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UEaseMover::UEaseMover()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UEaseMover::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the owning actor's root component has mobility set to movable.
    if(GetOwner()->GetRootComponent())
    {
        GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
    }

    // Initialize the starting location to the actor's current location.
    StartLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UEaseMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Perform the movement logic in each tick.
    MasterMove(DeltaTime);
}

// Determines movement behavior
void UEaseMover::MasterMove(float DeltaTime)
{
    // Update the current location.
    CurrentLocation = GetOwner()->GetActorLocation();

    // Check if the movement should be continuous.
    if(BContinuousMovement == true)
    {
        FContinuousMove(DeltaTime);
    }
    else
    {
        // Determine if the movement should be in reverse or forward.
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

// Function for smoothstep interpolation: Provides ease-in and ease-out motion.
FVector UEaseMover::SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
    float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha); // Calculate the smoothstep value of Alpha.
    return FMath::Lerp(Current, Target, SmoothAlpha); // Linearly interpolate between the current and target locations using the smoothstep value
}

// Function for forward movement
void UEaseMover::FMoveForward(float DeltaTime)
{
    if(!BMoveReverse)
    {
        // Set the target location for forward movement.
        TargetLocation = StartLocation + MoveOffset;

        // Calculate the interpolation factor (Alpha).
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);

        // Interpolate the location using smoothstep.
        FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);

        // Update the actor's location.
        GetOwner()->SetActorLocation(NewLocation);

        // Check if the movement is complete and switch to reverse movement.
        if(FVector::Distance(CurrentLocation, TargetLocation) <= 0.1f)
        {
            BMoveReverse = true;
            StartLocation = TargetLocation;
            StartTime = GetWorld()->GetTimeSeconds(); // Reset the start time for the reverse move
        }
    }
}

// Function for reverse movement
void UEaseMover::FMoveReverse(float DeltaTime)
{
    if(BMoveReverse)
    {
        // Set the target location for reverse movement.
        TargetLocation = StartLocation - MoveOffset;

        // Calculate the interpolation factor (Alpha).
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);

        // Interpolate the location using smoothstep.
        FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
        
        // Update the actor's location.
        GetOwner()->SetActorLocation(NewLocation);

        // Check if the movement is complete and switch to forward movement.
        if(FVector::Distance(CurrentLocation, TargetLocation) <= 0.1f)
        {
            BMoveReverse = false;
            StartLocation = TargetLocation;
            StartTime = GetWorld()->GetTimeSeconds(); // Reset the start time for the forward move
        }
    }
}


// Function for continuous movement
void UEaseMover::FContinuousMove(float DeltaTime)
{
    // Determine the target location based on the current movement direction.
    TargetLocation = BMoveReverse ? CurrentLocation - MoveOffset : CurrentLocation + MoveOffset;
    
    // Calculate the interpolation factor (Alpha).
    float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);

    // Interpolate the location using smoothstep.
    FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
    
    // Update the actor's location.
    GetOwner()->SetActorLocation(NewLocation);
}