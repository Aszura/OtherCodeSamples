// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CameraSample.h"
#include "CameraSampleCharacter.h"

ACameraSampleCharacter::ACameraSampleCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Disable Jump and Duck actions
	bAddDefaultMovementBindings = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = false;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	// Disable collisions
	GetCollisionComponent()->bGenerateOverlapEvents = false;
	GetCollisionComponent()->SetCollisionProfileName("NoCollision");

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
}

void ACameraSampleCharacter::ChangeCameraArmLength(float changeValue)
{
	CameraBoom->TargetArmLength += changeValue * CameraZoomSpeed;
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, MinCameraZoom, MaxCameraZoom); //Clamp to min/max zoom level
}

void ACameraSampleCharacter::RotateCameraArm(FRotator rotation)
{
	CameraBoom->AddRelativeRotation(rotation * CameraRotationSpeed);
}

void ACameraSampleCharacter::MoveCharacterForward(float changeValue)
{
	//To change the movement speed, change max speed/acceleration/deceleration values 
	//on the floating pawn movement component of the character blueprint
	AddMovementInput(GetActorForwardVector(), changeValue);
}

void ACameraSampleCharacter::MoveCharacterRight(float changeValue)
{
	AddMovementInput(GetActorRightVector(), changeValue);
}