// Fill out your copyright notice in the Description page of Project Settings.

#include "GameController.h"
#include "UIController.h"
#include <string> 

// Sets default values
AGameController::AGameController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameController::BeginPlay()
{
	Super::BeginPlay();
	currentTime = maxTime;
	playerCached = GetWorld()->GetFirstPlayerController();

	uiController->ShowStartScreen("Try getting a green orb in 30 seconds!");
}

// Called every frame
void AGameController::Tick(float DeltaTime)
{
	if (paused)
		return;

	Super::Tick(DeltaTime);
	currentTime -= DeltaTime;

	uiController->SetTime(FString(std::to_string((int)currentTime).c_str()));

	if (currentTime <= 0)
		uiController->ShowEndGame("You ran out of time! Try again!");
}

void AGameController::Restart()
{
	playerCached->ConsoleCommand("RestartLevel");
}

void AGameController::SetPause(bool state)
{
	if(state)
		playerCached->SetInputMode(FInputModeUIOnly());
	else
		playerCached->SetInputMode(FInputModeGameOnly());

	playerCached->bShowMouseCursor = state;

	paused = state;
}

