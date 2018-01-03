// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"


class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8 
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	   UPawnSensingComponent* SensingComponent ;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigators, const FVector& Location, float Volume);
	UFUNCTION()
		void ResetRot();

	EAIState GuardState = EAIState::Idle;

	void SetGuardState(EAIState newState);
	UFUNCTION(BlueprintImplementableEvent,Category = "AI")
	   void OnStateChanged(EAIState newState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	//DO-NOT-CHANGE
	FRotator OriginalRot = FRotator::ZeroRotator;
	FTimerHandle Reset_Rot_TimerHandle;
	
	
};
