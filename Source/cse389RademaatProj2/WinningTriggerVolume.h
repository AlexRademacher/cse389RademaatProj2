// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "WinningTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class CSE389RADEMAATPROJ2_API AWinningTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Constructor for setting default values for this actor
	AWinningTriggerVolume();

	// Overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// Overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
