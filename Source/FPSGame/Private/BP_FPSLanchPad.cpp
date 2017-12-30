// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_FPSLanchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSGameCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABP_FPSLanchPad::ABP_FPSLanchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FVector forwardDirect = GetActorForwardVector();
	ForceStrength = FVector(forwardDirect.X * 400, forwardDirect.Y * 400, 1500.0f);

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPad mesh"));
	RootComponent = LaunchPadMesh;

	OverlappedArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapped Area"));
	OverlappedArea->SetupAttachment(RootComponent);
	OverlappedArea->SetBoxExtent(FVector(200.0f));
	OverlappedArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlappedArea->OnComponentBeginOverlap.AddDynamic(this,&ABP_FPSLanchPad::LaunchPadOverlapeed);



}

// Called when the game starts or when spawned
void ABP_FPSLanchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABP_FPSLanchPad::LaunchPadOverlapeed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults)
{
	AFPSGameCharacter* gameChar = Cast<AFPSGameCharacter>(OtherActor);
	if (gameChar)
	{
		gameChar->LaunchCharacter(ForceStrength,true,true);
		UGameplayStatics::SpawnEmitterAtLocation(this, ForceParticleSystem, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(ForceStrength, NAME_None, false);
		UGameplayStatics::SpawnEmitterAtLocation(this, ForceParticleSystem, GetActorLocation());
	}
}

// Called every frame
void ABP_FPSLanchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

