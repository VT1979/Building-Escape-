// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Door.generated.h"

class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Returns mass of actors in kilograms
	virtual float GetTotalMassOfActorsOnPlate(ATriggerVolume* PressurePlate);

	// Investigate whether Player is overlapping
	virtual bool IsPlayerOverlapping(ATriggerVolume* PressurePlate);

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
	
	//UPROPERTY(EditDefaultsOnly)
	//ATriggerVolume* PressurePlate = nullptr;

	//Threshhold on the pressure plate to open door
	UPROPERTY(EditAnywhere)
	float PressurePlateThreshold = 11.f;

	AActor* Owner = nullptr;
		
};
