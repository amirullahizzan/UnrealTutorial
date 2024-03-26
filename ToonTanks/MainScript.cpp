// MainScript.cpp
#include "MainScript.h"
#include "Kismet/GameplayStatics.h"

AMainScript::AMainScript()
{
    // Constructor
}

void AMainScript::BeginPlay()
{
    Super::BeginPlay();

    AController* Controller = UGameplayStatics::GetPlayerController(this, 0);
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    PlayerController->bShowMouseCursor = true;
    // Called when the level starts
}

void AMainScript::CustomLevelEvent()
{
    // Implement your level-specific logic here
}
