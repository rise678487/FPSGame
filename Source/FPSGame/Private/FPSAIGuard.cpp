// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameGameMode.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	SensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	SensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	OriginalRot = GetActorRotation();
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
	AFPSGameGameMode* GM = Cast<AFPSGameGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->MissionComplete(SeenPawn,false);
	}
	
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigators, const FVector& Location, float Volume)
{
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	if (NoiseInstigators == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 50.0f, 12.0f, FColor::Blue, false, 10);
	GetWorldTimerManager().ClearTimer(Reset_Rot_TimerHandle);
	GetWorldTimerManager().SetTimer(Reset_Rot_TimerHandle,this, &AFPSAIGuard::ResetRot, 3.0f);
	SetActorRotation(NewLookAt);
}


void AFPSAIGuard::ResetRot()
{
	SetActorRotation(OriginalRot);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


