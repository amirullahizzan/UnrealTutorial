// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComponent->SetupAttachment(CapsuleComponent);

	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComponent->SetupAttachment(BaseMeshComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMeshComponent);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::RotateTurret(FVector LookAtTarget, float InterpSpeed)
{
	FVector TurretLocation = TurretMeshComponent->GetComponentLocation();
	//FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();

	FVector ToTarget = LookAtTarget - TurretLocation;
	// FRotator LookAtRotation = ToTarget.Rotation();
	// LookAtRotation.Roll = 0.f;
	// LookAtRotation.Pitch = 0.f;

	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	FRotator CurrentRotation = TurretMeshComponent->GetComponentRotation();
	TurretMeshComponent->SetWorldRotation(
		FMath::RInterpTo(CurrentRotation,LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),InterpSpeed)
		);
	// TurretMeshComponent = LookAtTarget;

	// LookAt(TurretMeshComponent->GetComponentLocation(),CursorHitLocation);
}


