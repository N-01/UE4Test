// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactible.h"
#include "OctopusCharacter.h"

AInteractible::AInteractible()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractible::Activate(AOctopusCharacter* usedBy) {
	
}

