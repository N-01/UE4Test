// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "OctopusCharacter.h"
#include "UIController.h"
#include <algorithm>

ADoor::ADoor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	targetAngle = isOpen ? openState : closedState;
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float rotation = openSpeed * DeltaTime;

	if (currentAngle < targetAngle)
		currentAngle = std::min(currentAngle + rotation, targetAngle);
	else if (currentAngle > targetAngle)
		currentAngle = std::max(currentAngle - rotation, targetAngle);

	doorTransform->SetActorRotation(FQuat::MakeFromEuler(FVector(0, 0, currentAngle)));
}

void ADoor::Activate(AOctopusCharacter* usedBy)
{
	if (requiredKey == KeyColor::None || usedBy->ownedKeys[requiredKey])
	{
		isOpen = !isOpen;
		targetAngle = isOpen ? openState : closedState;

		if(requiredKey != KeyColor::None)
			usedBy->RemoveKey(requiredKey);
	}
	else {
		usedBy->uiController->ShowNotification(FString::Printf(L"You need a %s key", KeyColorToString(requiredKey)), 2);
	}
}

