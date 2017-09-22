// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UHUDWidget::Initialize() {
	Super::Initialize();
	notifyTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(L"NotificationText")));
	timerText = Cast<UTextBlock>(GetWidgetFromName(FName(L"Timer")));
	keyBox = Cast<UHorizontalBox>(GetWidgetFromName(FName(L"Items")));

	startScreen = Cast<UCanvasPanel>(GetWidgetFromName(FName(L"StartScreen")));
	startText = Cast<UTextBlock>(GetWidgetFromName(FName(L"GreetingMessage")));
	goButton = Cast<UButton>(GetWidgetFromName(FName(L"OkButton")));

	endGameScreen = Cast<UCanvasPanel>(GetWidgetFromName(FName(L"EndGameScreen")));
	endText = Cast<UTextBlock>(GetWidgetFromName(FName(L"FinalMessage")));
	playAgainButton = Cast<UButton>(GetWidgetFromName(FName(L"PlayAgain")));
	return true;
}

UHUDWidget::~UHUDWidget()
{
}