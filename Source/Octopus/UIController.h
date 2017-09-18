// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMG.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/Actor.h"
#include "UIController.generated.h"

class AGameController;

UCLASS()
class OCTOPUS_API AUIController : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	AGameController* gameController;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowNotification"))
	void ShowNotification(const FString &text, float duration);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetTime"))
	void SetTime(const FString &text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddKey"))
	void AddKey(const KeyColor key);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RemoveKey"))
	void RemoveKey(const KeyColor key);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowEndGame"))
	void ShowEndGame(const FString &text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowStartScreen"))
	void ShowStartScreen(const FString &text);

	// Sets default values for this actor's properties
	AUIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
