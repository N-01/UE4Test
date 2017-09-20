// Fill out your copyright notice in the Description page of Project Settings.

#include "UIController.h"
#include "GameController.h"
#include "MainUI.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include <algorithm>


void AUIController::ShowEndGame(const FString & text)
{
	m_uiWidget->endGameScreen->SetVisibility(ESlateVisibility::Visible);
	m_uiWidget->playAgainButton->OnClicked.AddDynamic(this, &AUIController::OnPlayAgain);
	m_uiWidget->endText->SetText(FText::FromString(text));

	playerCached->SetInputMode(FInputModeUIOnly());
	playerCached->bShowMouseCursor = true;

	gameController->SetPause(true);
}

void AUIController::ShowStartScreen(const FString & text)
{
	m_uiWidget->startScreen->SetVisibility(ESlateVisibility::Visible);
	m_uiWidget->goButton->OnClicked.AddDynamic(this, &AUIController::OnStartPlay);
	m_uiWidget->startText->SetText(FText::FromString(text));

	playerCached->SetInputMode(FInputModeUIOnly());
	playerCached->bShowMouseCursor = true;

	UUserWidget* pButtonWidget = CreateWidget<UUserWidget>(GetWorld(), m_uiWidget->KeyTemplate);
	pButtonWidget->AddToViewport();
	auto image = Cast<UImage>(pButtonWidget->GetWidgetFromName(FName(TEXT("Icon"))));
	image->SetBrushFromTexture(LoadTextureFromPath("/Game/Materials/BlueKeyTexture"));
	m_uiWidget->keyBox->AddChild(pButtonWidget);

	gameController->SetPause(true);
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

