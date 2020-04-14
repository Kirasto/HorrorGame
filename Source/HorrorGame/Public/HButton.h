// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractable.h"
#include "HButton.generated.h"

USTRUCT()
struct FHEvent 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, Category = "Event")
	AHInteractable* InteractWith;
	UPROPERTY(EditInstanceOnly, Category = "Event")
	bool bSetOn;

	FHEvent()
	{
		InteractWith = NULL;
		bSetOn = true;
	}
};

/**
 * 
 */
UCLASS()
class HORRORGAME_API AHButton : public AHInteractable
{
	GENERATED_BODY()
	
private:
protected:
	UPROPERTY(EditInstanceOnly, Category = "Button")
	TArray<FHEvent> InteractEvents;
public:
	void Interact() override;
};
