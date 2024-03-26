// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Movement Modifier", meta = (AllowPrivateAccess = "true"))
	float RotatorSpeed = 4.0f;
	UPROPERTY(VisibleAnywhere, Category = "Movement Modifier", meta = (AllowPrivateAccess = "true"))
	float Speed = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmComponent;

private:
	AController *Controller;
	APlayerController* PlayerController;
	FHitResult CursorHitResult;
	bool bIsHit = false;

	void Fire();
	void Move(float Value);
	void Turn(float Value);
    void DebugMarkOnMouse();
};
