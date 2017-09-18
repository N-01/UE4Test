// Fill out your copyright notice in the Description page of Project Settings.

#include "FinishButton.h"
#include "OctopusCharacter.h"
#include "UIController.h"

void AFinishButton::Activate(AOctopusCharacter* usedBy) {
	usedBy->uiController->ShowEndGame("Congratulations, you have basic patten matching skills! Now go for another exciting challenge!");
}