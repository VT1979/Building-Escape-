// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#define OUT // to remind myself of outparameters in method calls

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
	
	if (!ensure(PressurePlate)) { return 0; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	UE_LOG(LogTemp, Warning, TEXT("%s: Pressureplate successful"), *PressurePlate->GetName())

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

bool UDoor::IsPlayerOverlapping()
{
	if (!ensure(PressurePlate)) { return false; }
	
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	if (OverlappingActors.Num() != 0){
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor == GetWorld()->GetFirstPlayerController()->GetOwner()) {
				return true;
			}
		}
	
	}
	return false;
}
