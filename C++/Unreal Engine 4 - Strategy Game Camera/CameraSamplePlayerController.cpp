// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CameraSample.h"
#include "CameraSamplePlayerController.h"
#include "CameraSampleCharacter.h"
#include "Engine/LocalPlayer.h"

ACameraSamplePlayerController::ACameraSamplePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
}

void ACameraSamplePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ACameraSamplePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ACameraSamplePlayerController::OnMoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &ACameraSamplePlayerController::OnMoveRightAxis);
	InputComponent->BindAxis("MouseHorizontal", this, &ACameraSamplePlayerController::OnMouseHorizontalAxis);
	InputComponent->BindAxis("MouseVertical", this, &ACameraSamplePlayerController::OnMouseVerticalAxis);
	InputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ACameraSamplePlayerController::OnZoomInAction);
	InputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &ACameraSamplePlayerController::OnZoomOutAction);
	InputComponent->BindAction("LookAround", EInputEvent::IE_Pressed, this, &ACameraSamplePlayerController::OnLookAroundStartAction);
	InputComponent->BindAction("LookAround", EInputEvent::IE_Released, this, &ACameraSamplePlayerController::OnLookAroundStopAction);
}

void ACameraSamplePlayerController::OnMoveForwardAxis(float axisValue)
{
	APawn* const Pawn = GetPawn();
	ACameraSampleCharacter* character = Cast<ACameraSampleCharacter>(Pawn);
	if (character)
	{
		character->MoveCharacterForward(axisValue);
	}
}

void ACameraSamplePlayerController::OnMoveRightAxis(float axisValue)
{
	APawn* const Pawn = GetPawn();
	ACameraSampleCharacter* character = Cast<ACameraSampleCharacter>(Pawn);
	if (character)
	{
		character->MoveCharacterRight(axisValue);
	}
}

void ACameraSamplePlayerController::OnMouseHorizontalAxis(float axisValue)
{
	if (lookAroundEnabled)
	{
		APawn* const Pawn = GetPawn();
		Pawn->AddControllerYawInput(axisValue);
		Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
	}
}
void ACameraSamplePlayerController::OnMouseVerticalAxis(float axisValue)
{
	if (lookAroundEnabled)
	{
		APawn* const Pawn = GetPawn();
		ACameraSampleCharacter* character = Cast<ACameraSampleCharacter>(Pawn);
		if (character)
		{
			character->RotateCameraArm(FRotator(axisValue, 0.0f, 0.0f));
		}
		Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
	}
}

void ACameraSamplePlayerController::OnZoomInAction()
{
	APawn* const Pawn = GetPawn();
	ACameraSampleCharacter* character = Cast<ACameraSampleCharacter>(Pawn);
	if (character)
	{
		character->ChangeCameraArmLength(-1.0f);
	}
}

void ACameraSamplePlayerController::OnZoomOutAction()
{
	APawn* const Pawn = GetPawn();
	ACameraSampleCharacter* character = Cast<ACameraSampleCharacter>(Pawn);
	if (character)
	{
		character->ChangeCameraArmLength(1.0f);
	}
}

void ACameraSamplePlayerController::OnLookAroundStartAction()
{
	//Lock mouse cursor
	lookAroundEnabled = true;
	bShowMouseCursor = false;
	InputComponent->bBlockInput = true;
	mouseLockPositionX = Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->GetMouseX();
	mouseLockPositionY = Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->GetMouseY();
}

void ACameraSamplePlayerController::OnLookAroundStopAction()
{
	//Unlock mouse cursor
	lookAroundEnabled = false;
	bShowMouseCursor = true;
	InputComponent->bBlockInput = false;
}