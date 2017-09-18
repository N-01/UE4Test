// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameController.generated.h"

class AUIController;

UCLASS()
class OCTOPUS_API AGameController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	AUIController* uiController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
	float maxTime = 30;

	float currentTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
