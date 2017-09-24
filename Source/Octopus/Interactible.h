// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UMG.h"
#include "Components/WidgetComponent.h"

#include "Interactible.generated.h"

class AOctopusCharacter;

UCLASS()
class OCTOPUS_API AInteractible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractible();

	virtual void Activate(AOctopusCharacter* usedBy);
};
