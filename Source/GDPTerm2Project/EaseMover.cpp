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
    
    if(GetOwner()->GetRootComponent())
    {
        GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
    }
    StartLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UEaseMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    MasterMove(DeltaTime);
}

// Master Move Function
void UEaseMover::MasterMove(float DeltaTime)
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


// Function for ease motion
FVector UEaseMover::SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
    float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
    return FMath::Lerp(Current, Target, SmoothAlpha);
}

// Function for forward movement
void UEaseMover::FMoveForward(float DeltaTime)
{
    if(!BMoveReverse)
    {
        TargetLocation = StartLocation + MoveOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);
        FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
        GetOwner()->SetActorLocation(NewLocation);

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
        TargetLocation = StartLocation - MoveOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);
        FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
        GetOwner()->SetActorLocation(NewLocation);

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
    TargetLocation = BMoveReverse ? CurrentLocation - MoveOffset : CurrentLocation + MoveOffset;
    float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / MoveTime, 0.0f, 1.0f);
    FVector NewLocation = SmoothstepInterp(CurrentLocation, TargetLocation, Alpha);
    GetOwner()->SetActorLocation(NewLocation);
}