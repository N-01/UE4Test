// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.h"
#include "Key.h"
#include "Door.generated.h"

UCLASS()
class OCTOPUS_API ADoor : public AInteractible
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* doorTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	KeyColor requiredKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float openSpeed = 180;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float openState = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float closedState = 0;

	float currentAngle = 0;
	float targetAngle = 0;

	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate(AOctopusCharacter* usedBy) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetRotation"))
	void SetRotation(float targetAngle);
};
