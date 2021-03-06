// Fill out your copyright notice in the Description page of Project Settings.

#include "UIController.h"
#include "GameController.h"
#include "HUDWidget.h"
#include "InteractionPrompt.h"

#include <algorithm>

//////////////////////////////////////////
//INIT

AUIController::AUIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUIController::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if(uiWidgetRef.ComponentProperty.IsNone() == false)
		hudWidget = Cast<UHUDWidget>(Cast<UWidgetComponent>(uiWidgetRef.GetComponent(this))->GetUserWidgetObject());
}

void AUIController::BeginPlay()
{
	Super::BeginPlay();
}

//////////////////////////////////////////
//BASIC TEXT ELEMENTS

void AUIController::ShowNotification(const FString &text, float duration) {
	hudWidget->notifyTextBlock->SetText(FText::FromString(text));
	hudWidget->notifyTextBlock->SetVisibility(ESlateVisibility::Visible);
	notificationTimeLeft = duration;
}

void AUIController::SetTime(const FString &text)
{
	hudWidget->timerText->SetText(FText::FromString(text));
}

//////////////////////////////////////////
//KEYS

void AUIController::AddKey(const KeyColor key)
{
	//caching widgets and textures
	//in this game it's pointless, but i would do it in a real one

	if (keyWidgets.find(key) != keyWidgets.end()) {
		keyWidgets[key]->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		keyWidgets[key] = CreateWidget<UUserWidget>(GetWorld(), hudWidget->KeyTemplate);
	}

	UUserWidget* keyWidget = keyWidgets[key];
	
	auto image = Cast<UImage>(keyWidget->GetWidgetFromName(FName(TEXT("Icon"))));

	if (keyTextures.find(key) == keyTextures.end())
		keyTextures[key] = LoadTextureFromPath(FString(L"/Game/Materials/") + KeyColorToString(key) + L"KeyTexture");

	image->SetBrushFromTexture(keyTextures[key]);

	keyWidget->AddToViewport();
	hudWidget->keyBox->AddChild(keyWidget);
}

void AUIController::RemoveKey(const KeyColor key)
{
	if (keyWidgets.find(key) != keyWidgets.end()) {
		keyWidgets[key]->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//////////////////////////////////////////
//MENU SCREENS

void AUIController::ShowScreen(UCanvasPanel* screen)
{
	screen->SetVisibility(ESlateVisibility::Visible);
	gameController->SetPause(true);
}

void AUIController::ShowEndGame(const FString & text)
{
	hudWidget->playAgainButton->OnClicked.AddDynamic(this, &AUIController::OnPlayAgain);
	hudWidget->endText->SetText(FText::FromString(text));

	ShowScreen(hudWidget->endGameScreen);
}

void AUIController::ShowStartScreen(const FString & text)
{
	hudWidget->goButton->OnClicked.AddDynamic(this, &AUIController::OnStartPlay);
	hudWidget->startText->SetText(FText::FromString(text));

	ShowScreen(hudWidget->startScreen);
}

void AUIController::ShowInteractFor(AActor* actor) {
	if (actor != nullptr)
		interactPrompt->SetActorLocation(actor->GetActorLocation());
	interactPrompt->Show(actor != nullptr);
}

void AUIController::OnPlayAgain()
{
	gameController->Restart();
}

void AUIController::OnStartPlay()
{
	hudWidget->startScreen->SetVisibility(ESlateVisibility::Collapsed);
	gameController->SetPause(false);
}

//////////////////////////////////////////
//EXTRA
void AUIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (notificationTimeLeft > 0) {
		notificationTimeLeft = std::max(notificationTimeLeft - DeltaTime, 0.0f);

		if (notificationTimeLeft < 1e-5) {
			hudWidget->notifyTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

UTexture2D* AUIController::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return NULL;

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Path)));
}

