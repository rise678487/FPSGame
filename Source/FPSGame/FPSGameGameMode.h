// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameGameMode.generated.h"

UCLASS(minimalapi)
class AFPSGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameGameMode();
	UFUNCTION()
	    void MissionComplete(APawn* InstigatorPawn,bool bMissionSuccess);
	UFUNCTION(BlueprintImplementableEvent,Category = "Events")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
		TSubclassOf<AActor> SpectatingViewportClasses;
};



