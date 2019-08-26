// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
//#include "GameFramework/Actor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	/*

	Owner = GetOwner();

	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Component OpenDoor's owner not found!"))
	}	

	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate trigger volume not initialised"))
	}

	*/
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the TriggerVolume
	if(GetTotalMassOfActorsOnPlate() > PressurePlateThreshold) 
	{
		OnOpen.Broadcast();
	}

	else
	{
		OnClose.Broadcast();
	}
}




