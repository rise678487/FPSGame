// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "FPSGameCharacter.h"
#include "FPSGameGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapedBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlaped Box"));
	OverlapedBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapedBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapedBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapedBox->SetBoxExtent(FVector(200.0f));
	OverlapedBox->SetHiddenInGame(false);
	RootComponent = OverlapedBox;

	OverlapedBox->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	DecalComponent->DecalSize = FVector(200.0f);
	DecalComponent->SetupAttachment(OverlapedBox);
}



void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Overlap Box"));
	UE_LOG(LogTemp, Warning, TEXT("Overlap box"));
	AFPSGameCharacter* character = Cast<AFPSGameCharacter>(OtherActor);
	if (!character)
	{
		return;
	}
	if (character->bIsCarryingObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Overlap Box"));
		UE_LOG(LogTemp, Warning, TEXT("Overlap box"));
		AFPSGameGameMode* GM = Cast<AFPSGameGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->MissionComplete(character);
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this,ObjectiveMissingSound,GetActorLocation());
	}
}



