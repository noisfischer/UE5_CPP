// Fill out your copyright notice in the Description page of Project Settings.


#include "floatingActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component and attach to actor root
	FloatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	FloatMesh->SetupAttachment(RootComponent);

	// Find UE5 starter cube as the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	// If the mesh is found, attach it to root and set its location
	if(MeshAsset.Succeeded())
		FloatMesh->SetStaticMesh(MeshAsset.Object);
		FloatMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// Set Default Values
	FloatSpeed = 5.0f;
	FloatRange = 25.0f;
	RotationSpeed = 100.0f;
	Time = 0.0f;

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	// Save initial location of actor
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	
	// Create a new location for actor based on sin wave
	FVector NewLocation = StartLocation;
	NewLocation.Z += FMath::Sin(Time * FloatSpeed) * FloatRange;

	// Create new rotation for actor
	FRotator NewRotation = GetActorRotation();
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	// Set the new location and rotation for every Tick of Delta Time ^^^
	SetActorLocationAndRotation(NewLocation, NewRotation);

}

#if WITH_EDITOR
void AFloatingActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	StartLocation = GetActorLocation();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


