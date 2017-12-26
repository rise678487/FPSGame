// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlackHoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black Hole Mesh"));
	BlackHoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BlackHoleMesh;
//
	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere"));
	InnerSphereComp->SetSphereRadius(100.0f);
	InnerSphereComp->SetupAttachment(BlackHoleMesh);

	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::InnererSphereOverlap);
	
	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere"));
	OuterSphereComponent->SetSphereRadius(3000.0f);
	OuterSphereComponent->SetupAttachment(BlackHoleMesh);
	
	

}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AFPSBlackHole::InnererSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
	if (OtherActor)
	{
		OtherActor->Destroy();
		
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OuterSphereComponent->GetOverlappingComponents(OverlappedComponents);
	for (UPrimitiveComponent* overlappedComp : OverlappedComponents)
	{
		const float radius = OuterSphereComponent->GetScaledSphereRadius();
		const float Force = -2000.0f;
		overlappedComp->AddRadialForce(GetActorLocation(), radius, Force, ERadialImpulseFalloff::RIF_Constant, true);
	}
	

}

