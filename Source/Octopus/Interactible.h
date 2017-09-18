// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.generated.h"

class AOctopusCharacter;

UCLASS()
class OCTOPUS_API AInteractible : public AActor
{
	GENERATED_BODY()
	
public:	
	bool isCloseToPlayer = false;

	FEditorScriptExecutionGuard ScriptGuard;

	// Sets default values for this actor's properties
	AInteractible();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetCaptionVisibility"))
	void SetCaptionVisibility(bool state);

	virtual void Activate(AOctopusCharacter* usedBy);

	virtual void ShowWidget(bool state);

protected:

	bool widgetVisible = false;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
};
