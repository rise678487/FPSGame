// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* InnerSphereComp;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* OuterSphereComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent* BlackHoleMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InnererSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	TArray<UPrimitiveComponent*> OverlappedComponents;


	
	
};