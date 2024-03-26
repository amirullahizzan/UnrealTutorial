// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //Find Player Tank
    APawn* TankPawn = UGameplayStatics::GetPlayerPawn(this,0);
    Tank = Cast<ATank>(TankPawn);
    if(!Tank)return;
    float TargetDistance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if(TargetDistance <= PlayerNoticeRange )
    {
    RotateTurret(Tank->GetActorLocation(),1);
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
}

void ATower::Fire()
{
    
}
