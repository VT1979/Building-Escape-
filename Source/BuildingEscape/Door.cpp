// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#define OUT

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!ensure(Owner)) { return; }

	// ...
	
}


// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return 0; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Only execute if there are overlapping actors
	if (OverlappingActors.Num() > 0)
	{
		///Add each actor's mass
		for (AActor* Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}

	}
	return TotalMass;
}
