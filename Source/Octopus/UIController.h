// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Key.h"
#include <map>

#include "UMG.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/Actor.h"
#include "UIController.generated.h"

class AGameController;
class UHUDWidget;
class AInteractionPrompt;

UCLASS()
class OCTOPUS_API AUIController : public AActor
{
	GENERATED_BODY()

	float notificationTimeLeft = 0;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	AGameController* gameController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	AInteractionPrompt* interactPrompt;

	UPROPERTY(EditAnywhere, Category = References)
	FComponentReference uiWidgetRef;


	UHUDWidget* hudWidget;
	
	std::map<KeyColor, UUserWidget*> keyWidgets;
	std::map<KeyColor, UTexture2D*> keyTextures;

	void ShowNotification(const FString &text, float duration);
	void SetTime(const FString &text);

	void AddKey(const KeyColor key);
	void RemoveKey(const KeyColor key);

	void ShowEndGame(const FString &text);
	void ShowStartScreen(const FString &text);

	void ShowInteractFor(AActor* actor = nullptr);

	UFUNCTION()
	void OnPlayAgain();
	UFUNCTION()
	void OnStartPlay();

	// Sets default values for this actor's properties
	AUIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void ShowScreen(UCanvasPanel* screen);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UTexture2D* LoadTextureFromPath(const FString& Path);
	
	
};
