// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UHUDWidget::Initialize() {
	Super::Initialize();
	notifyTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("NotificationText"))));
	timerText = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Timer"))));
	keyBox = Cast<UHorizontalBox>(GetWidgetFromName(FName(TEXT("Items"))));

	startScreen = Cast<UCanvasPanel>(GetWidgetFromName(FName(TEXT("StartScreen"))));
	startText = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("GreetingMessage"))));
	goButton = Cast<UButton>(GetWidgetFromName(FName(TEXT("OkButton"))));

	endGameScreen = Cast<UCanvasPanel>(GetWidgetFromName(FName(TEXT("EndGameScreen"))));
	endText = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("FinalMessage"))));
	playAgainButton = Cast<UButton>(GetWidgetFromName(FName(TEXT("PlayAgain"))));
	return true;
}

UHUDWidget::~UHUDWidget()
{
}