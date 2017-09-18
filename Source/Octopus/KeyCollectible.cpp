// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyCollectible.h"
#include "OctopusCharacter.h"

void AKeyCollectible::Activate(AOctopusCharacter* usedBy)
{
	usedBy->AddKey(color);
	Destroy();
}

