// Fill out your copyright notice in the Description page of Project Settings.


#include "PacingEnemy.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
APacingEnemy::APacingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision"));
	PlayerAttackCollision->SetupAttachment(GetMesh(), TEXT("Sphere"));

	CanAttackPlayer = false;

	StartLocation = GetActorLocation().X;
	Direction = 1;
}

// Called when the game starts or when spawned
void APacingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerAttackCollision->OnComponentBeginOverlap.AddDynamic(this,
		&APacingEnemy::OnPlayerAttackOverlapBegin);

	PlayerAttackCollision->OnComponentEndOverlap.AddDynamic(this,
		&APacingEnemy::OnPlayerAttackOverlapEnd);
}

// Called every frame
void APacingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rot = GetActorRotation();

	if (GetActorLocation().Y >= StartLocation + 200) {
		//Direction = -1;
		UE_LOG(LogTemp, Warning, TEXT("Turning back"));

		if (Rot.Yaw <= 0) {
			Rot.Yaw -= 180.0f;
			SetActorRotation(Rot);
		}
	}
	else if (GetActorLocation().Y <= StartLocation - 200) {
		//Direction = 1;
		UE_LOG(LogTemp, Warning, TEXT("Turning forward"));

		if (Rot.Yaw >= 180) {
			Rot.Yaw += 180.0f;
			SetActorRotation(Rot);
		}
	}

	FVector LocAdjustment = FVector(200.f * DeltaTime * Direction, 0.f, 0.f);
	AddActorLocalOffset(LocAdjustment);
}

// Called to bind functionality to input
void APacingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacingEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		CanAttackPlayer = true;

		// deal damage to the player
		Player->Damage();
		//UE_LOG(LogTemp, Warning, TEXT("Player Damaged"));

		CanAttackPlayer = false;
	}
}

void APacingEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		CanAttackPlayer = false;
	}
}

