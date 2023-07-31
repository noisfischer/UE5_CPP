// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component and attach to actor root
	MovingPlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MovingPlatformMesh->SetupAttachment(RootComponent);

	// Find UE5 starter cube as the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	// If the mesh is found, attach it to root and set its location
	if(MeshAsset.Succeeded())
		MovingPlatformMesh->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// // Add two variables together
	// MyNewNumber = InputAInt + InputBFloat;
	//
	// MyVector = GetActorLocation();

	// Set Start Location to Actor spawn point
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// Method 1 of moving platform	
	// // Set local variable
	// FVector LocalVector = MyVector;
	// // Move platform forward in Y location by 1 each tick of gameplay
	// MyVector.Y = MyVector.Y + 1;
	// SetActorLocation(LocalVector);

// // Method 2 of moving platform
// 	
// 	// Get Current Location by creating a local variable
// 	FVector CurrentLocation = GetActorLocation();
//
// 	// Use expression to update the location of the platform
// 	CurrentLocation.Y = CurrentLocation.Y + 1;
// 	
// 	// Set Location
// 	SetActorLocation(CurrentLocation);

// Method 3 of moving platform - to specified vector location
	
	// Get current actor location
	FVector CurrentLocation = GetActorLocation();

	// Add current location vector to platform velocity vector (speed of platform) using Delta Time (frame rate independent)
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;

	// Location of platform updates as per the above statement
	SetActorLocation(CurrentLocation);

// Bounce platform back to starting position once it reaches a max distance away from start position
	
	// :: looks at the functions within the FVector class. Looking for the distance between start and current location vectors
	DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);

	// If the platform moves too far from start position, it will update its start position and move in the opposite direction
	if (DistanceMoved > MaxMoveDistance)
	{
		// Creates new local variable that gets the full forward direction of the platform velocity vector
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		
		// Set new start location
		StartLocation = StartLocation + MoveDirection * MaxMoveDistance;
		SetActorLocation(StartLocation);
		
		// Reverse direction
		PlatformVelocity = -PlatformVelocity;
	}
	
	
	
}

