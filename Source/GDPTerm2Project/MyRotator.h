#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyRotator.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDPTERM2PROJECT_API UMyRotator : public UActorComponent
{
	GENERATED_BODY()

public: 
	// Sets default values for this component's properties
	UMyRotator();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FRotator StartRotation;
	FRotator CurrentRotation;
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, Category="Rotate", meta=(ClampMin="0", ClampMax="20", UIMin="0", UIMax="20"))
	float RotationTime = 5.0f;  // default value

	UPROPERTY(EditAnywhere, Category="Rotate")
	FRotator RotateOffset;

	// Current elapsed time since rotation started
	float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BRotateReverse;

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BContinuousRotation;

	// Private Functions
	void MasterRotate(float DeltaTime);
	void FRotateForward(float DeltaTime);
	void FRotateReverse(float DeltaTime);
	void FContinuousRotate(float DeltaTime);
	void ApplyRotation(float DeltaTime);
	float CubicEaseInOut(float t);
};

