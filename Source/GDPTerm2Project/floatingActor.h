// Fill out your copyright notice in the Description page of Project Settings.

// makes code structure more efficient and optimized
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floatingActor.generated.h"

UCLASS()
class GDPTERM2PROJECT_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	//called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif	

	//getting a component and naming it
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FloatMesh; 

	//creating an editable property of the actor's float height range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "FloatingActor")
	float FloatRange;

	//creating an editable property of the actor's float speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "FloatingActor")
	float FloatSpeed;
	
	//creating an editable property of the actor's rotation speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "FloatingActor")
	float RotationSpeed;

	//define a variable for the start location which will be used in the cpp file
	FVector StartLocation;

	//create float variable for time
	float Time;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
