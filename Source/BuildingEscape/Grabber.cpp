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

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::Grab()
{
	// Line Trace and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach(); 
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If we hit something attach a physics handle
	if(ActorHit)
	{
		if (!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponentAtLocationWithRotation(
		ComponentToGrab,
		NAME_None,
		ComponentToGrab->GetOwner()->GetActorLocation(),
		FRotator(0.f, 0.f, 0.f) ///do not allow rotation
		);	
	}	
}

void UGrabber::Release()
{
	///Release physics handle
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
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

FVector UGrabber::CalculateLineTraceEnd()
{
	// method GetPlayerViewPoint actually modifies its parameters
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LineTraceEnd = CalculateLineTraceEnd();

	/// if the physics handle is attached 
	if (!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		/// then move object that we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	FVector LineTraceEnd = CalculateLineTraceEnd();

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
	
	return Hit;
}