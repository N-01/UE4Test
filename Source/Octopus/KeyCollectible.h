// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "Key.h"
#include "KeyCollectible.generated.h"

/**
 * 
 */
UCLASS()
class OCTOPUS_API AKeyCollectible : public AInteractible
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	KeyColor color;
	
	virtual void Activate(AOctopusCharacter* usedBy) override;
	
};
