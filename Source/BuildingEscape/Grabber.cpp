// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/Public/CollisionQueryParams.h"

#define OUT // empty macro, used to annotate the out_ variables in GetPlayerViewPoint() below

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));

	/// Line Trace and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	/// If we hit something attach a physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));

	///Release physics handle
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::FindPhysicsHandleComponent()
{
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		///nothing happens
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), 
			*GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PawnInput)
		{
			UE_LOG(LogTemp, Warning, TEXT("%Input component found"))

			//Bind the input actions
			PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
			PawnInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
			//CAREFUL HERE: IN THE ABOVE LINE YOU STILL HAVE TO USE THE "Grab"
			//NAME BECAUSE WE ARE DETECTING A RELEASE OF THE GRAB ACTION
		}
	else
		{
			UE_LOG(LogTemp, Error, TEXT("%s missing pawn input component"), 
				*GetOwner()->GetName())
		}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// if the physics handle is attached then move object
	/// that we are holding
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// method GetPlayerViewPoint actually modifies its parameters
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	
	/*
	// Draw a red trace to visualise
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, 
		FColor(255,0,0), false, 0.f, 0.f, 10.f);
	*/

	FHitResult Hit;

	/// Set up parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")),
		false,
		GetOwner()
	);

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You grabbed %s"), *ActorHit->GetName())
	}

	return Hit;
}