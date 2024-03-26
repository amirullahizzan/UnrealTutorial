// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLoc = GetActorLocation();
	FString MyString = "Nama 123 @$$";

	// UE_LOG(LogTemp, Display, TEXT("Start Loc : %f"),startLoc);
	UE_LOG(LogTemp, Display, TEXT("String : %s"), *MyString);
	// UE_LOG(LogTemp, Warning, TEXT("Your message"));
	// UE_LOG(LogTemp, Error, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	// currentPos.Dist(speedVector,currentPos);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	//    FHitResult Hit; if(Hit.)
	RotatePlatform(DeltaTime);
	if (ShouldPlatformReturn())
	{
		// FString ActorName = GetName();
		// UE_LOG(LogTemp, Display, TEXT("Object : %s,"), *ActorName);
		// float OvershotDistance = DistanceMoved - MaxMoveDistance;
		// UE_LOG(LogTemp, Display, TEXT("Overshot : %f"), OvershotDistance);
		FVector MoveDir = SpeedVector.GetSafeNormal();
		StartLoc = StartLoc + MoveDir * MaxMoveDistance;
		SetActorLocation(StartLoc);
		SpeedVector = -SpeedVector; // flip when reach certain distance
	}
	else
	{
		FVector CurrentLoc = GetActorLocation();
		CurrentLoc = CurrentLoc + (SpeedVector * DeltaTime);
		SetActorLocation(CurrentLoc);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//FRotator CurrentRotation = GetActorRotation();
	//SetActorRotation(CurrentRotation); //Goes over negative and infinity
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MaxMoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	//float DistanceMoved = FVector::Dist(StartLoc, GetActorLocation());
	return FVector::Dist(StartLoc, GetActorLocation());
}
