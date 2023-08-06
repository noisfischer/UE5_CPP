#include "MyRotator.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMyRotator::UMyRotator()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentTime = 0.0f;
}

// Called when the game starts
void UMyRotator::BeginPlay()
{
    Super::BeginPlay();

    // Set owner actor to Movable on begin play
    if (GetOwner()->GetRootComponent())
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
void UMyRotator::ApplyRotation(float DeltaTime)
{
    CurrentTime += DeltaTime;
    float Alpha = FMath::Clamp(CurrentTime / RotationTime, 0.0f, 1.0f);
    float EasedAlpha = CubicEaseInOut(Alpha);

    FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, EasedAlpha);
    GetOwner()->SetActorRotation(NewRotation);
}

// Function for forward rotation
void UMyRotator::FRotateForward(float DeltaTime)
{
    TargetRotation = StartRotation + RotateOffset;
    ApplyRotation(DeltaTime);

    if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
    {
        BRotateReverse = true;
        StartRotation = TargetRotation;
        CurrentTime = 0.0f; // Resetting the CurrentTime
    }
}

// Function for reverse rotation
void UMyRotator::FRotateReverse(float DeltaTime)
{
    TargetRotation = StartRotation - RotateOffset;
    ApplyRotation(DeltaTime);

    if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
    {
        BRotateReverse = false;
        StartRotation = TargetRotation;
        CurrentTime = 0.0f; // Resetting the CurrentTime
    }
}

// Function for continuous rotation
void UMyRotator::FContinuousRotate(float DeltaTime)
{
    TargetRotation = (BRotateReverse) ? CurrentRotation - RotateOffset : CurrentRotation + RotateOffset;
    ApplyRotation(DeltaTime);
}

float UMyRotator::CubicEaseInOut(float t)
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
