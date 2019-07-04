// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenDoor::OpenDoor()
{	
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	
	// Report the rotation to the output log
	/*
	FString ObjectName = Owner->GetName();
	FString ObjectRotation = Owner->GetActorRotation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("The rotation of %s is %s"), *ObjectName, *ObjectRotation);
	*/
	
}

void UOpenDoor::CloseDoor()
{	
		Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));	
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the TriggerVolume
	if(GetTotalMassOfActorsOnPlate() > PressurePlateThreshhold) ///TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Only execute if there are overlapping actors
	if (OverlappingActors.Num() > 0)
	{
		///Add each actor's mass
		for (AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapping with: %s"), *Actor->GetName())
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
		
	}
	return TotalMass;
}

