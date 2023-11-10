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
    
    if(GetOwner()->GetRootComponent())
    {
        GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
    }
    StartScale = GetOwner()->GetRootComponent()->GetComponentScale();
}

// Called every frame
void UScaler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    MasterScale(DeltaTime);
}

// Master Scale Function
void UScaler::MasterScale(float DeltaTime)
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

// Function for ease motion
FVector UScaler::SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha)
{
    float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
    return FMath::Lerp(Current, Target, SmoothAlpha);
}

// Function for scaling up
void UScaler::FScaleUp(float DeltaTime)
{
    if(!bScaleReverse)
    {
        TargetScale = StartScale + ScaleOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = true;
            StartScale = TargetScale;
            StartTime = GetWorld()->GetTimeSeconds();
        }
    }
}

// Function for scaling down
void UScaler::FScaleDown(float DeltaTime)
{
    if(bScaleReverse)
    {
        TargetScale = StartScale - ScaleOffset;
        float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);
        FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
        GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);

        if(FVector::Distance(CurrentScale, TargetScale) <= 0.1f)
        {
            bScaleReverse = false;
            StartScale = TargetScale;
            StartTime = GetWorld()->GetTimeSeconds();
        }
    }
}

// Function for continuous scaling
void UScaler::FContinuousScale(float DeltaTime)
{
    TargetScale = bScaleReverse ? CurrentScale - ScaleOffset : CurrentScale + ScaleOffset;
    float Alpha = FMath::Clamp((GetWorld()->GetTimeSeconds() - StartTime) / ScaleTime, 0.0f, 1.0f);
    FVector NewScale = SmoothstepInterp(CurrentScale, TargetScale, Alpha);
    GetOwner()->GetRootComponent()->SetWorldScale3D(NewScale);
}
