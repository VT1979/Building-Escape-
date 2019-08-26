// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "OpenDoor.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

//Child class of UDoor to handle opening of a closed door
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UPROPERTY (BlueprintAssignable)
	//FDoorEvent OnOpen;

	//UPROPERTY (BlueprintAssignable)
	//FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	//UPROPERTY(EditAnywhere)
	//ATriggerVolume* PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere) switched off in subsequent lesson
	//AActor* Owner = nullptr;
	
	//Returns mass of actors in kilograms
	//float GetTotalMassOfActorsOnPlate();

	//Threshhold on the pressure plate to open door
	//UPROPERTY(EditAnywhere)
	//float PressurePlateThreshold = 11.f;
};
