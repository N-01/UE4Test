// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactible.h"
#include "OctopusCharacter.h"

AInteractible::AInteractible()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractible::BeginPlay()
{
	Super::BeginPlay();

	widgetComponent = Cast<UWidgetComponent>(uiWidgetRef.GetComponent(this));
	widgetComponent->SetVisibility(false);
}

void AInteractible::Activate(AOctopusCharacter* usedBy) {
	
}

void AInteractible::ShowWidget(bool state) {
	if (widgetVisible != state) {
		widgetComponent->SetVisibility(state);
		widgetVisible = state;
	}
}

