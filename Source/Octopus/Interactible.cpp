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

	//I couldn't find any working method to disable Widget rendering with no Blueprint involved
	SetCaptionVisibility(false);
}

void AInteractible::Activate(AOctopusCharacter* usedBy) {
	
}

void AInteractible::ShowWidget(bool state) {
	if (widgetVisible != state) {
		SetCaptionVisibility(state);
		widgetVisible = state;
	}
}

