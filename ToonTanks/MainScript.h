// MainScript.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainScript.generated.h"

UCLASS()
class TOONTANKS_API AMainScript : public ALevelScriptActor
{
    GENERATED_BODY()

public:
    // Constructor
    AMainScript();

    // Called when the level is loaded
    virtual void BeginPlay() override;

    // Add any level-specific logic or event functions here
    void CustomLevelEvent();
};
