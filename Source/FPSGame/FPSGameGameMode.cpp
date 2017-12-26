// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameGameMode.h"
#include "FPSGameHUD.h"
#include "FPSGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AFPSGameGameMode::AFPSGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSGameHUD::StaticClass();

}

void AFPSGameGameMode::MissionComplete(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
	}
	if (SpectatingViewportClasses)
	{
		TArray<AActor*> ReturnedActors;
		AActor* NewTarget = nullptr;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewportClasses, ReturnedActors);
		if (ReturnedActors.Num() > 0)
		{
			NewTarget = ReturnedActors[0];
		}
		OnMissionCompleted(InstigatorPawn);
		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		if (PC)
		{
			PC->SetViewTargetWithBlend(NewTarget, 1.0f, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::MakeRandomColor(),TEXT("Spectating Viewport Classes is empty..Please Add reference to it"));
	}
}
