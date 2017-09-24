// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionPrompt.h"
#include "UMG.h"
#include "Components/WidgetComponent.h"


// Sets default values
AInteractionPrompt::AInteractionPrompt()
{
}

// Called when the game starts or when spawned
void AInteractionPrompt::BeginPlay()
{
	Super::BeginPlay();

	if (interactibleWidgetRef.ComponentProperty.IsNone() == false)
		interactibleWidget = Cast<UWidgetComponent>(interactibleWidgetRef.GetComponent(this))->GetUserWidgetObject();
}

void AInteractionPrompt::Show(bool state)
{
	interactibleWidget->SetVisibility(state ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
