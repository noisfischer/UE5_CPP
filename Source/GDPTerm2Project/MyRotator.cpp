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

    // Ensure the owning actor's root component has mobility set to movable.
    if (GetOwner()->GetRootComponent())
    {
        GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
    }

    // Initialize the start rotation to the actor's current rotation.
    StartRotation = GetOwner()->GetActorRotation();
}

// Called every frame
void UMyRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Perform the rotation logic in each tick.
    MasterRotate(DeltaTime);
}

// Determines rotation behavior
void UMyRotator::MasterRotate(float DeltaTime)
{
    // Update the current rotation.
    CurrentRotation = GetOwner()->GetActorRotation();

    // Check if the rotation should be continuous.
    if (BContinuousRotation)
    {
        FContinuousRotate(DeltaTime);
    }
    else
    {
        // Determine if the rotation should be in reverse or forward.
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

// Calculates and applies the new rotation to the actor.
void UMyRotator::ApplyRotation(float DeltaTime)
{
    // Update the current time for rotation.
    CurrentTime += DeltaTime;
    // Calculate the interpolation factor (Alpha).
    float Alpha = FMath::Clamp(CurrentTime / RotationTime, 0.0f, 1.0f);
    // Apply easing function for smooth transition.
    float EasedAlpha = CubicEaseInOut(Alpha);

    // Interpolate the rotation using Lerp and apply it to the actor.
    FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, EasedAlpha);
    GetOwner()->SetActorRotation(NewRotation);
}

// Function for forward rotation
void UMyRotator::FRotateForward(float DeltaTime)
{
    // Set the target rotation for forward rotation.
    TargetRotation = StartRotation + RotateOffset;
    
    // Apply the rotation.
    ApplyRotation(DeltaTime);

    // Check if the rotation is complete and switch to reverse rotation.
    if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
    {
        BRotateReverse = true;
        StartRotation = TargetRotation;
        CurrentTime = 0.0f; // Reset the current time.
    }
}

// Function for reverse rotation
void UMyRotator::FRotateReverse(float DeltaTime)
{
    // Set the target rotation for reverse rotation.
    TargetRotation = StartRotation - RotateOffset;
    ApplyRotation(DeltaTime);
    
    // Check if the rotation is complete and switch to forward rotation.
    if (FMath::Abs((CurrentRotation - TargetRotation).GetNormalized().Yaw) <= 0.1f)
    {
        BRotateReverse = false;
        StartRotation = TargetRotation;
        CurrentTime = 0.0f; // Reset the current time.
    }
}

// Function for continuous rotation
void UMyRotator::FContinuousRotate(float DeltaTime)
{
    // Determine the target rotation based on the current rotation direction
    TargetRotation = (BRotateReverse) ? CurrentRotation - RotateOffset : CurrentRotation + RotateOffset;

    // Apply the rotation.
    ApplyRotation(DeltaTime);
}

// Easing function for smooth rotation.
float UMyRotator::CubicEaseInOut(float t)
{

    // Check if 't' is in the first half of the animation duration.
    if (t < 0.5f)
    {
        // If 't' is less than 0.5, apply cubic acceleration starting slow and then increasing in speed.
        // This part handles the 'ease-in' portion of the animation.
        // 't * t * t' creates a cubic curve, making the start of the rotation slower.
        // Multiplying by 4 increases the rate of acceleration to match the midpoint value (0.5 when t is 0.5).
        return 4.0f * t * t * t;
    }
    else
    {
        // If 't' is 0.5 or more, handle the 'ease-out' portion of the animation.
        // The 'ease-out' starts fast and slows down towards the end.
        // 'f' is the adjusted time value for the second half. It ranges from -0.5 to 0.
        float f = t - 1.0f;
        
        // The cubic curve ('f * f * f') slows down the movement as it approaches the end.
        // Adding 1.0f ensures that the output smoothly transitions to 1 as 't' approaches 1.
        // This results in a decelerating motion towards the end of the animation.
        return 1.0f + 4.0f * f * f * f;
    }
}
