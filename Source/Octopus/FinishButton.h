// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "FinishButton.generated.h"

/**
 * 
 */
UCLASS()
class OCTOPUS_API AFinishButton : public AInteractible
{
	GENERATED_BODY()
	
	virtual void Activate(AOctopusCharacter* usedBy) override;
	
	
};
