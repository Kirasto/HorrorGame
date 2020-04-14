// Fill out your copyright notice in the Description page of Project Settings.


#include "HInteractable.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AHInteractable::AHInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	bIsOnOffSystem = true;
	bIsSwitchOnOff = true;
	bIsOn = false;
	bIsSelected = false;

	bIsLocked = false;
}

// Called when the game starts or when spawned
void AHInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHInteractable::SetOn(bool bSetOn)
{
	if (bIsOnOffSystem == false || (bIsSwitchOnOff == false && bIsOn == true)) return;

	bSetOn ? On() : Off();
}

void AHInteractable::Interact()
{
	if (bIsOnOffSystem && bIsSwitchOnOff)
	{
		SetOn(!bIsOn);
	}
	else
	{
		SetOn(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Has Interact !!"));
}

void AHInteractable::On()
{
	bIsOn = true;
}

void AHInteractable::Off()
{
	bIsOn = false;
}

void AHInteractable::Lock()
{
	bIsLocked = true;
}

void AHInteractable::UnLock()
{
	bIsLocked = false;
}