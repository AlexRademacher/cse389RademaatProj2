// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up our Visual component to hold our mesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// Find the Tripyramid shape
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		VisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid"));

	// If we successfully found the Tripyramid shape, set the mesh component to it
	if (VisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(VisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	PlayerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision"));
	PlayerCollision->SetupAttachment(VisualMesh, TEXT("Sphere"));
	PlayerCollision->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	PlayerCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));

	CanCollect = false;
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ACollectable::OnPlayerOverlapBegin);

	PlayerCollision->OnComponentEndOverlap.AddDynamic(this,
		&ACollectable::OnPlayerOverlapEnd);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rot = GetActorRotation();

	Rot.Yaw += 30.0f * DeltaTime;
	SetActorRotation(Rot);

}

void ACollectable::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		CanCollect = true;

		int CurrentScore = Player->GetScore();

		Player->SetScore(CurrentScore + 1);

		CanCollect = false;

		Destroy();
	}
}

void ACollectable::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		CanCollect = false;
	}
}
