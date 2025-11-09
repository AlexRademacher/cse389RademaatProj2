// Fill out your copyright notice in the Description page of Project Settings.


#include "WinningTriggerVolume.h"
#include "Kismet/GameplayStatics.h"

void AWinningTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

AWinningTriggerVolume::AWinningTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AWinningTriggerVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWinningTriggerVolume::OnOverlapEnd);
}

void AWinningTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s entered the trigger volume"), *OtherActor->GetName());
	UGameplayStatics::OpenLevel(GetWorld(), FName("WinMenuLevel"));
}

void AWinningTriggerVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s exited the trigger volume"), *OtherActor->GetName());
}
