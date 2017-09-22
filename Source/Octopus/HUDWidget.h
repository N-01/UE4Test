// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "HUDWidget.generated.h"

/*
 * This script is used as a reference storage,
 * it is the closest i could find to a sane person's
 * component access pattern in this engine
 */
UCLASS()
class OCTOPUS_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTextBlock* notifyTextBlock, *startText, *endText, *timerText;
	UCanvasPanel* startScreen, *endGameScreen;
	UButton* goButton, *playAgainButton;
	UHorizontalBox* keyBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> KeyTemplate;

	virtual bool Initialize() override;

	UHUDWidget(const FObjectInitializer& ObjectInitializer);
	~UHUDWidget();
};
