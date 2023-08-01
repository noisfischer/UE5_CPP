// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchBP.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitchBP::ALightSwitchBP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set up point light
	DesiredIntensity = 5000.0f;
	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetAttenuationRadius(500.0f);
	PointLight1->SetVisibility(true);
	RootComponent = PointLight1;

	// set up collision sphere
	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->SetHiddenInGame(false);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchBP::OnOverlapBegin);
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchBP::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ALightSwitchBP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALightSwitchBP::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}


void ALightSwitchBP::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}


void ALightSwitchBP::ToggleLight()
{
	PointLight1->ToggleVisibility();
}
