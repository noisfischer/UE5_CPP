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
	// Internal rotation values used for rotation logic.
	FRotator StartRotation; // Initial rotation of the component.
	FRotator CurrentRotation; // Current rotation of the component.
	FRotator TargetRotation; // Target rotation to reach.

	UPROPERTY(EditAnywhere, Category="Rotate", meta=(ClampMin="0", ClampMax="20", UIMin="0", UIMax="20"))
	float RotationTime = 5.0f;  // Total time for the rotation to complete.

	UPROPERTY(EditAnywhere, Category="Rotate")
	FRotator RotateOffset; // Target rotation

	// Current elapsed time since rotation started
	float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BRotateReverse; // Flag for reversing the rotation.

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BContinuousRotation; // Flag for continuous rotation.

	// Private Functions for rotation logic
	void MasterRotate(float DeltaTime); // Master function to determine rotation type.
	void FRotateForward(float DeltaTime); // Function to handle forward rotation.
	void FRotateReverse(float DeltaTime); // Function to handle reverse rotation.
	void FContinuousRotate(float DeltaTime); // Function to handle continuous rotation.
	void ApplyRotation(float DeltaTime); // Applies the calculated rotation to the actor.
	float CubicEaseInOut(float t); // Easing function for smooth rotation.
};

