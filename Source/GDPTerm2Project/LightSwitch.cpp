// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up point light
	DesiredIntensity = 5000.0f;
	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(true);
	PointLight1->SetAttenuationRadius(500.0f);
	RootComponent = PointLight1;

	// Set up collision sphere
	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1")); // create sphere collision
	Sphere1->InitSphereRadius(250.0f); // set radius of collision
	Sphere1->SetupAttachment(RootComponent); // attach to point light root component
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitch::OnOverlapBegin); // begin overlap
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitch::OnOverlapEnd); // end overlap
	Sphere1->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALightSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp) // this is itself (not overlapping itself)
	{
		ToggleLight();
	}
}


void ALightSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}


void ALightSwitch::ToggleLight()
{
	PointLight1->ToggleVisibility();
}




