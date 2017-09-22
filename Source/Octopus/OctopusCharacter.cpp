// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "OctopusCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include <math.h>
#include "EngineUtils.h"
#include "UIController.h"
#include "Classes/Kismet/GameplayStatics.h"

//////////////////////////////////////////
//IMPORTANT STUFF

void AOctopusCharacter::Tick(float DeltaTime) {
	

	//look for interactibles: if it's close enough,
	//in less than 90deg angle to camera vector
	//and accessible to raycast, then you can use it
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractible::StaticClass(), FoundActors);

	auto pos = GetTransform().GetLocation();
	AInteractible* found = nullptr;

	for (size_t i = 0; i < FoundActors.Num(); i++)
	{
		auto interactible = (AInteractible*)FoundActors[i];
		auto otherPos = interactible->GetTransform().GetLocation();
		auto diff = (pos - otherPos);

		if (diff.Size() < 150) {
			diff.Normalize();

			auto angle = acos(FVector::DotProduct(diff, FollowCamera->GetForwardVector()));
			if (angle > PI / 2) {
				FHitResult HitInfo(ForceInit);
				FVector cameraToInteractible = FollowCamera->GetComponentLocation() - otherPos;

				GetWorld()->LineTraceSingleByChannel(HitInfo, FollowCamera->GetComponentLocation(), -cameraToInteractible * 300, ECollisionChannel::ECC_WorldStatic, TraceParams);

				if (Cast<AInteractible>(HitInfo.GetActor()))
					found = interactible;
			}
		}

		interactible->ShowWidget(found != nullptr);

		if(found != nullptr)
			break;
	}

	closestInteractible = found;
}

void AOctopusCharacter::Interact() {
	if(closestInteractible != nullptr)
		closestInteractible->Activate(this);
}

void AOctopusCharacter::AddKey(KeyColor key) {
	ownedKeys.insert_or_assign(key, true);
	uiController->AddKey(key);
}

void AOctopusCharacter::RemoveKey(KeyColor key)
{
	ownedKeys[key] = false;
	uiController->RemoveKey(key);
}


//////////////////////////////////////////
//BASE UNREAL STUFF


AOctopusCharacter::AOctopusCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AOctopusCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AOctopusCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOctopusCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AOctopusCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AOctopusCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AOctopusCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AOctopusCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AOctopusCharacter::OnResetVR);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AOctopusCharacter::Interact);
}

void AOctopusCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AOctopusCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AOctopusCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AOctopusCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AOctopusCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AOctopusCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOctopusCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
