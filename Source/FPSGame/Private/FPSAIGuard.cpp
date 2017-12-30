// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	SensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	SensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Seen  %s"), *SeenPawn->GetName());
	if(SeenPawn == nullptr)
	{ 
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12.0f, FColor::Red, false, 10.0f);
	
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigators, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("Heard :%s"),*NoiseInstigators->GetName());
	if (NoiseInstigators == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 100.0f, 12.0f, FColor::Blue, false, 10);
}


// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


