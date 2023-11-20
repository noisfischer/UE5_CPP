#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Scaler.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GDPTERM2PROJECT_API UScaler : public UActorComponent
{
	GENERATED_BODY()

public:
	UScaler();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Internal scaling values used for scaling logic.
	FVector StartScale; // Initial scale of the component.
	FVector TargetScale; // Target scale to reach.
	FVector CurrentScale; // Current scale of the component.

	// Main function to determine scaling type.
	void MasterScale(float DeltaTime);
	// Function for smoothstep interpolation: Provides ease-in and ease-out scaling.
	FVector SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha);
	// Function to handle scaling up.
	void FScaleUp(float DeltaTime);
	// Function to handle scaling down.
	void FScaleDown(float DeltaTime);
	// Function to handle continuous scaling.
	void FContinuousScale(float DeltaTime);

	// Scaling properties.
	UPROPERTY(EditAnywhere, Category = "Scaling")
	FVector ScaleOffset; // Target scale

	UPROPERTY(EditAnywhere, Category = "Scaling")
	float ScaleTime; // Total time for the scaling to complete.

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bScaleReverse; // Flag for reversing the scaling.

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bContinuousScaling; // Flag for continuous scaling.

	float StartTime; // Time when the scaling started.
};
