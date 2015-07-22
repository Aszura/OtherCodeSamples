// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "CameraSamplePlayerController.generated.h"

UCLASS()
class ACameraSamplePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACameraSamplePlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers. */
	void OnMoveForwardAxis(float axisValue);
	void OnMoveRightAxis(float axisValue);
	void OnMouseHorizontalAxis(float axisValue);
	void OnMouseVerticalAxis(float axisValue);
	void OnZoomInAction();
	void OnZoomOutAction();
	void OnLookAroundStartAction();
	void OnLookAroundStopAction();
private:
	bool lookAroundEnabled = false;
	int32 mouseLockPositionX;
	int32 mouseLockPositionY;
};


