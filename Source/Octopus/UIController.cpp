// Fill out your copyright notice in the Description page of Project Settings.

#include "UIController.h"
#include "GameController.h"
#include "MainUI.h"

#include <algorithm>

AUIController::AUIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUIController::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if(uiWidgetRef.ComponentProperty.IsNone() == false)
		m_uiWidget = Cast<UMainUI>(Cast<UWidgetComponent>(uiWidgetRef.GetComponent(this))->GetUserWidgetObject());
}

void AUIController::BeginPlay()
{
	Super::BeginPlay();
}

void AUIController::ShowNotification(const FString &text, float duration) {
	m_uiWidget->notifyTextBlock->SetText(FText::FromString(text));
	m_uiWidget->notifyTextBlock->SetVisibility(ESlateVisibility::Visible);
	notificationTimeLeft = duration;
}

void AUIController::SetTime(const FString &text)
{
	m_uiWidget->timerText->SetText(FText::FromString(text));
}

void AUIController::AddKey(const KeyColor key)
{
	//caching widgets and textures
	//in this game it's pointless, but i would do it in a real one

	if (keyWidgets.find(key) != keyWidgets.end()) {
		keyWidgets[key]->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		keyWidgets[key] = CreateWidget<UUserWidget>(GetWorld(), m_uiWidget->KeyTemplate);
	}

	UUserWidget* keyWidget = keyWidgets[key];
	
	auto image = Cast<UImage>(keyWidget->GetWidgetFromName(FName(TEXT("Icon"))));

	if (keyTextures.find(key) == keyTextures.end())
		keyTextures[key] = LoadTextureFromPath(FString(L"/Game/Materials/") + KeyColorToString(key) + L"KeyTexture");

	image->SetBrushFromTexture(keyTextures[key]);

	keyWidget->AddToViewport();
	m_uiWidget->keyBox->AddChild(keyWidget);
}

void AUIController::RemoveKey(const KeyColor key)
{
	if (keyWidgets.find(key) != keyWidgets.end()) {
		keyWidgets[key]->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUIController::ShowScreen(UCanvasPanel* screen)
{
	screen->SetVisibility(ESlateVisibility::Visible);

	playerCached->SetInputMode(FInputModeUIOnly());
	playerCached->bShowMouseCursor = true;

	gameController->SetPause(true);
}

void AUIController::ShowEndGame(const FString & text)
{
	m_uiWidget->playAgainButton->OnClicked.AddDynamic(this, &AUIController::OnPlayAgain);
	m_uiWidget->endText->SetText(FText::FromString(text));

	ShowScreen(m_uiWidget->endGameScreen);
}

void AUIController::ShowStartScreen(const FString & text)
{
	m_uiWidget->goButton->OnClicked.AddDynamic(this, &AUIController::OnStartPlay);
	m_uiWidget->startText->SetText(FText::FromString(text));

	ShowScreen(m_uiWidget->startScreen);
}

void AUIController::OnPlayAgain()
{
	gameController->Restart();
}

void AUIController::OnStartPlay()
{
	m_uiWidget->startScreen->SetVisibility(ESlateVisibility::Collapsed);
	playerCached->SetInputMode(FInputModeGameOnly());
	playerCached->bShowMouseCursor = false;
	gameController->SetPause(false);
}

// Called every frame
void AUIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (notificationTimeLeft > 0) {
		notificationTimeLeft = std::max(notificationTimeLeft - DeltaTime, 0.0f);

		if (notificationTimeLeft < 1e-5) {
			m_uiWidget->notifyTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

UTexture2D* AUIController::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return NULL;

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Path)));
}

