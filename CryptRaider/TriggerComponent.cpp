// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    // UE_LOG(LogTemp, Display, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
    Mover = NewMover;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetTaggedActor())
    {
        if (Mover)
        {
            Mover->SetShouldMove(false);
        }
    }
    // else
    {
        // do smth
        // float Time = GetWorld()->GetTimeSeconds();
        // FString OverlappingActorName = GetTaggedActor()->GetActorNameOrLabel();
        // UE_LOG(LogTemp, Display, TEXT("UNLOCKING : %s, %f"), *OverlappingActorName, Time);
    }

    if (!Mover)
    {
        return;
    }
    else
    {
        AActor *TaggedActor = GetTaggedActor();
        // UPrimitiveComponent* TaggedComponent = TaggedActor->GetComponentByClass<UPrimitiveComponent>();
        // TaggedComponent->SetSimulatePhysics(false);
        if (!TaggedActor){return;}
            USceneComponent *TaggedRootParent = TaggedActor->GetRootComponent();
            UPrimitiveComponent *RootPrimitiveComponent = Cast<UPrimitiveComponent>(TaggedRootParent);
        // Cast to UPrimitiveComponent
        if (TaggedActor->ActorHasTag("Grabbed"))
        {
            return;
        }
        if (RootPrimitiveComponent)
        {
            // Attach actor to this component
            RootPrimitiveComponent->SetSimulatePhysics(false);
            // RootPrimitiveComponent->WakeAllRigidBodies(); // goes to sleep after awhile
        }
        TaggedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
        Mover->SetCollisionPhaseThrough();
    }

    // for (int32 i = 0; i < OverlappingActors.Num(); i++)
    {
        // FString OverlappingActorName = OverlappingActors[i]->GetActorNameOrLabel();
        // UE_LOG(LogTemp, Display, TEXT("OVERLAPPED : %s"), *OverlappingActorName);
        // if (OverlappingActorName == "SM_Gargoyle_Statue2")
        //{
        //     UE_LOG(LogTemp, Display, TEXT("OPEN SESAME"));
        // }
    }

    // uint32 actorscount = OverlappingActors.Num();
    // UE_LOG(LogTemp, Display, TEXT("TEST : %d"),actorscount);
}

AActor *UTriggerComponent::GetTaggedActor()
{
    TArray<AActor *> OverlappingActors;
    GetOverlappingActors(OverlappingActors);
    if (OverlappingActors.Num() > 0)
    {
        for (AActor *Actor : OverlappingActors) // Collection types for loops
        {
            if (Actor->ActorHasTag(TagName))
            {
                return Actor;
            }
            // FString OverlappingActorName = Actor->GetActorNameOrLabel();
            //   if (OverlappingActorName == "SM_Gargoyle_Statue2")
            {
                // UE_LOG(LogTemp, Display, TEXT("OPEN SESAME"));
            }
        }
    }
    else
    {
        // if (Mover)
        {
            // Mover->SetShouldMove(false);
        }
    }

    return nullptr;
}
