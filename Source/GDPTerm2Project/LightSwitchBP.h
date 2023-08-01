// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchBP.generated.h"

UCLASS()
class GDPTERM2PROJECT_API ALightSwitchBP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchBP();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="SwitchComponents") // create point light comp
	class UPointLightComponent* PointLight1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="SwitchComponents") // create collision sphere comp
	class USphereComponent* Sphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SwitchVariables") // desired light intensity
	float DesiredIntensity;

	UFUNCTION(BlueprintNativeEvent, Category="SwitchFunctions") // create functions for overlap begin
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnOverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintNativeEvent, Category="SwitchFunctions") // create functions for overlap end
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION() // toggle light visibility
	void ToggleLight();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
