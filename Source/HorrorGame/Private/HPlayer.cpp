// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayer.h"

#include "HInteractable.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include <HButton.h>

// Sets default values
AHPlayer::AHPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);

	SelectedInteractable = NULL;
}

// Called when the game starts or when spawned
void AHPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHPlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AHPlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AHPlayer::InteractAction()
{
	if (SelectedInteractable)
	{
		SelectedInteractable->Interact();
	}
}

void AHPlayer::CheckInteractable()
{
	FHitResult HitResult;

	FVector EyeLocation;
	FRotator EyeRotation;

	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * 1000);


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		AHInteractable* InteractableHit = Cast<AHInteractable>(HitResult.GetActor());

		if (InteractableHit && InteractableHit->IsLocked() == false)
		{
			SelectedInteractable = InteractableHit;
		}
	}
	else if (SelectedInteractable)
	{
		SelectedInteractable = NULL;
	}
}

// Called every frame
void AHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckInteractable();
}

// Called to bind functionality to input
void AHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHPlayer::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AHPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AHPlayer::AddControllerYawInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHPlayer::InteractAction);
}

