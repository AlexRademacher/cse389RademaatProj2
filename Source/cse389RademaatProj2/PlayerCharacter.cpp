// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Points = 0;
	Health = 100;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp = FindComponentByClass<UCapsuleComponent>();

	if (CollisionComp)
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind the actions
	PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PEI->BindAction(InputJump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
	PEI->BindAction(InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComponent->GetCollisionProfileName().ToString() == "Enemy")
	{
		Health -= 20;
		LaunchCharacter(-this->GetVelocity() * 5, false, false);
		UE_LOG(LogTemp, Warning, TEXT("%d"), Health);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr) {
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		// Foward/Backward direction
		if (MoveValue.Y != 0.f) {
			// Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}

		// Right/Left direction
		if (MoveValue.X != 0.f) {
			// Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddControllerYawInput(MoveValue.X);
			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetPawn<ACharacter>();

	if (!IsValid(Character)) {
		return;
	}

	Character->Jump();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr) {
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f) {
			AddControllerYawInput(LookValue.X);
		}

		if (LookValue.Y != 0.f) {
			AddControllerPitchInput(-LookValue.Y);
		}
	}
}

void APlayerCharacter::SetScore(int NewScore)
{
	Points = NewScore;
	UE_LOG(LogTemp, Warning, TEXT("%d"), Points);
}

int APlayerCharacter::GetScore()
{
	return Points;
}

int APlayerCharacter::GetHealth()
{
	return Health;
}

