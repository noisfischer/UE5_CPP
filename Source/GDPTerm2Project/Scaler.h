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
	FVector StartScale;
	FVector TargetScale;
	FVector CurrentScale;

	void MasterScale(float DeltaTime);
	FVector SmoothstepInterp(const FVector& Current, const FVector& Target, float Alpha);
	void FScaleUp(float DeltaTime);
	void FScaleDown(float DeltaTime);
	void FContinuousScale(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Scaling")
	FVector ScaleOffset;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	float ScaleTime;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bScaleReverse;

	UPROPERTY(EditAnywhere, Category = "Scaling")
	bool bContinuousScaling;

	float StartTime;
};
