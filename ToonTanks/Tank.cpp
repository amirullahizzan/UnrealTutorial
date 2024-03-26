// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
// #include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComponent->SetupAttachment(RootComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    // USceneComponent* RootParent = GetRootComponent();
    // APawn* Pawn = Cast<APawn>(RootComponent);
    {
        // UE_LOG(LogTemp, Warning, TEXT("PAWN REF DOESNT EXIST"));
    }
    {
        // Controller = Pawn->GetController();
    }
    // Controller = GetWorld()->GetFirstPlayerController();
    Controller = GetController();
    PlayerController = Cast<APlayerController>(Controller);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed,this, &ATank::Fire);
    // PlayerInputComponent->BindAxis(LeftClick, this, &ATank::DebugMarkOnMouse);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerController)
        return;
    // if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
    bIsHit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, CursorHitResult);
    if (bIsHit)
        RotateTurret(CursorHitResult.ImpactPoint, 5.0f);
}

void ATank::Move(float Value)
{
    // First Method
    // FVector DeltaLocation = FVector(0.0f,0.0f,0.0f);
    // UObject* Object;
    // UWorld* World = GetWorld();
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * 100 * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);

    // Second
    // FVector ActorLocation = GetActorLocation();
    // USceneComponent* SceneComp = GetRootComponent();
    // UPrimitiveComponent* ActorComponent = GetComponentByClass<UPrimitiveComponent>();
    // ActorComponent->AddForce(ActorLocation*Value*100); //capsule rolls.

    // AActor* Actor = GetOwner();
    // UE_LOG(LogTemp, Display, TEXT("Actor name : %s"), *Actor->GetActorNameOrLabel());
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * RotatorSpeed * 10 * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::DebugMarkOnMouse()
{
    DrawDebugSphere(GetWorld(), CursorHitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
}

void ATank::Fire()
{
    DebugMarkOnMouse();
}