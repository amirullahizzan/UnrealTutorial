// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
UPROPERTY(EditDefaultsOnly,Category = "Combat")
float PlayerNoticeRange = 700.0f;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void Fire();
class ATank* Tank = nullptr;
	
};
