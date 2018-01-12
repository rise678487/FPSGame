// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameGameMode.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine/Engine.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	SensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	SensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	OriginalRot = GetActorRotation();
	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	if (bPatrol)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, TEXT("Move To NExt Patrol in Begin Play"));
		MoveToNExtPatrol();
	}
	
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	GetWorldTimerManager().ClearTimer(Reset_Rot_TimerHandle);
	if(SeenPawn == nullptr)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("wew"));
		return;
	}
	

	SetGuardState(EAIState::Alerted);
	
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12.0f, FColor::Red, false, 10.0f);
	AFPSGameGameMode* GM = Cast<AFPSGameGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->MissionComplete(SeenPawn,false);
	}
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
	
	
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigators, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	if (GuardState != EAIState::Alerted)
	{
		SetGuardState(EAIState::Suspicious);
	} 
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
	SetActorRotation(NewLookAt);
	GetWorldTimerManager().ClearTimer(Reset_Rot_TimerHandle);
	GetWorldTimerManager().SetTimer(Reset_Rot_TimerHandle,this, &AFPSAIGuard::ResetRot, 3.0f);
	SetGuardState(EAIState::Suspicious);


	// Stop Moving if Patroling
	AController* Controller = GetController();
	if (Controller)
	{
		Controller->StopMovement();
	}
	
	
}


void AFPSAIGuard::ResetRot()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	SetGuardState(EAIState::Idle);
	SetActorRotation(OriginalRot);

	if (bPatrol)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, TEXT("Work here"));


		MoveToNExtPatrol(); 
	}

}

void AFPSAIGuard::SetGuardState(EAIState newState)
{
	if (GuardState == newState)
	{
		return;
	}
	GuardState = newState;
	OnStateChanged(newState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint)
	{
		
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();
		if (DeltaTime < 500)
		{
			MoveToNExtPatrol();
		//	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, TEXT("Move To NExt Patrol in Tick"));
		}
	}


}

void AFPSAIGuard::MoveToNExtPatrol()
{
	if (CurrentPatrolPoint != nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolpoint;
	}
	else 
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}
	UNavigationSystem::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

