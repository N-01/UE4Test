// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMG.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/Actor.h"
#include "UIController.generated.h"

class AGameController;
class UMainUI;

UCLASS()
class OCTOPUS_API AUIController : public AActor
{
	GENERATED_BODY()

	float notificationTimeLeft = 0;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	AGameController* gameController;

	UPROPERTY(EditAnywhere, Category = References)
	FComponentReference uiWidgetRef;

	UMainUI* m_uiWidget;
	APlayerController* playerCached;

	void ShowNotification(const FString &text, float duration);
	void SetTime(const FString &text);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddKey"))
	void AddKey(const KeyColor key);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RemoveKey"))
	void RemoveKey(const KeyColor key);

	void ShowEndGame(const FString &text);
	void ShowStartScreen(const FString &text);

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UTexture2D* LoadTextureFromPath(const FString& Path);
	
	
};
