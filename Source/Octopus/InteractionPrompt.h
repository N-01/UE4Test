// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionPrompt.generated.h"

UCLASS()
class OCTOPUS_API AInteractionPrompt : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = References)
	FComponentReference interactibleWidgetRef;

	UUserWidget* interactibleWidget;

	// Sets default values for this actor's properties
	AInteractionPrompt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void Show(bool state);

	
	
};
