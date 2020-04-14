// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HInteractable.generated.h"

class UStaticMeshComponent;

UCLASS()
class HORRORGAME_API AHInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Interactable")
	bool bIsOnOffSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Interactable", meta = (EditCondition = "bHasOnOffSystem"))
	bool bIsSwitchOnOff;

	UPROPERTY(EditAnywhere)
	bool bIsOn;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;

	UPROPERTY(BlueprintReadOnly)
	bool bIsLocked;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetOn(bool bSetOn);
	virtual void Interact();

	virtual void On();
	virtual void Off();

	void Lock();
	void Unlock();

	bool IsLocked() { return bIsLocked; }
};
