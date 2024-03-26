// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

	// FRotator Rotator = GetComponentRotation();
	// FString ComponentRotation = Rotator.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("ROTATION : %s"), *ComponentRotation);
	//  ...

	// float SecondsElapsed = GetWorld()->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("ROTATION : %f"), SecondsElapsed);
}

void UGrabber::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (!PhysicsHandle)
	{
		return;
	}
	UPrimitiveComponent *HitComponent = PhysicsHandle->GetGrabbedComponent();
	if (!HitComponent)
	{
		return;
	}
	HitComponent->WakeAllRigidBodies();
	PhysicsHandle->ReleaseComponent();
	HitComponent->GetOwner()->Tags.Remove("Grabbed"); // get owner of this Component

	UE_LOG(LogTemp, Display, TEXT("Released "));
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (!PhysicsHandle)
	{
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Grab "));

	FHitResult HitResult;
	bool IsHit = GetGrabableInReach(HitResult);

	if (IsHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);

		UPrimitiveComponent *HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies(); // goes to sleep after awhile
		AActor *HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Display, TEXT("Grabbed an object "));

		// UE_LOG(LogTemp, Display, TEXT("OBJECT HIT : %s"), *HitActor->GetActorNameOrLabel());
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
	// else
	{
		// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue,false,5);
	}
	// DrawDebugLine(GetWorld(),Start,End,FColor::Red);
	// sDrawDebugSphere(GetWorld(), End, 10, 10, FColor::Red,false,5);
}

UPhysicsHandleComponent *UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent *Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!Result)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL REF PHYSICS"));
	}
	return Result;
}

bool UGrabber::GetGrabableInReach(FHitResult &OutHitResult)
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(MaxGrabDistance);
	FHitResult HitResult;
	bool IsHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (IsHit)
	{
		// HitTags.Remove("Grabbed");
		// for(FName* HitTag : HitTags)
		{
			// if()
			{
				// HitTag->Add(Grabbed);
			}
		}
		OutHitResult = HitResult;
	}
	return IsHit;
}
