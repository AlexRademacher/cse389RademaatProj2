// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingEnemy.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AChasingEnemy::AChasingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision"));
	PlayerAttackCollision->SetupAttachment(GetMesh(), TEXT("Sphere"));

	CanAttackPlayer = false;
}

// Called when the game starts or when spawned
void AChasingEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerAttackCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AChasingEnemy::OnPlayerAttackOverlapBegin);

	PlayerAttackCollision->OnComponentEndOverlap.AddDynamic(this,
		&AChasingEnemy::OnPlayerAttackOverlapEnd);
	
}

// Called every frame
void AChasingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChasingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChasingEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AChasingEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		CanAttackPlayer = false;
	}
}

