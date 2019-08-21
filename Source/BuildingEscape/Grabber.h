// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 150.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* PawnInput = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();
	void Release();

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	// Find (assumed) attached input component
	void SetupInputComponent();

	// Store player's viewpoint location and rottion
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Calcuate the end of our line trace
	FVector CalculateLineTraceEnd();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
};
