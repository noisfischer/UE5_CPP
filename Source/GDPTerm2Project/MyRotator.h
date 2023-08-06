// Fill out your copyright notice in the Description page of Project Settings.

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	// Define variables and functions for rotate
	FRotator StartRotation;
	FRotator TargetRotation;
	FRotator CurrentRotation;
	
	UPROPERTY(EditAnywhere, Category="Rotate")
	FRotator RotateOffset;
	UPROPERTY(EditAnywhere, Category="Rotate", meta=(ClampMin="0", ClampMax="1000", UIMin="0", UIMax="1000"))
	float RotationTime = 1.0f;
	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BRotateReverse = false;
	UPROPERTY(EditAnywhere, Category="Rotate")
	bool BContinuousRotation = false;
	
	void MasterRotate(float DeltaTime);
	void FRotateReverse(float DeltaTime);
	void FRotateForward(float DeltaTime);
	void FContinuousRotate(float DeltaTime);
};

