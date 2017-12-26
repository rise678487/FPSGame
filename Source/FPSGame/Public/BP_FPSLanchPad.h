// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_FPSLanchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API ABP_FPSLanchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_FPSLanchPad();
public:
	UPROPERTY(EditDefaultsOnly, Category = " Components ")
		UBoxComponent* OverlappedArea;

	UPROPERTY(EditAnywhere, Category = " Components ")
		UStaticMeshComponent* LaunchPadMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	   void LaunchPadOverlapeed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
