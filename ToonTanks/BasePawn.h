// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

    void RotateTurret(FVector LookAtTarget, float InterpSpeed);
	
	//UPROPERTY(VisibleInstanceOnly); //Visible property when created in the world
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float MoveSpeed = 1.0f;
	//UPROPERTY(EditAnywhere);
	//UPROPERTY(EditDefaultsOnly);
	//UPROPERTY(EditInstanceOnly);
	//UPROPERTY(VisibleDefaultsOnly);

	//UPROPERTY(BlueprintReadWrite);
	//UPROPERTY(BlueprintReadOnly);

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement Modifiers", meta = (AllowPrivateAccess = "true")) 
	float MoveSpeed = 1.0f;
	//UPROPERTY(meta = (AllowPrivateAccess = "true"));

public:	
	// Called every frame

protected :
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" ,meta = (AllowPrivateAccess = "true")) 
UStaticMeshComponent* TurretMeshComponent;
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" ,meta = (AllowPrivateAccess = "true")) 
USceneComponent* ProjectileSpawnPoint;

private:
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" ,meta = (AllowPrivateAccess = "true")) 
class UCapsuleComponent* CapsuleComponent;
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components" ,meta = (AllowPrivateAccess = "true")) 
UStaticMeshComponent* BaseMeshComponent;


};
