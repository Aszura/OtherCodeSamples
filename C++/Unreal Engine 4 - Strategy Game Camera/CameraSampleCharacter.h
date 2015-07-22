// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/SpectatorPawn.h"
#include "CameraSampleCharacter.generated.h"

UCLASS(Blueprintable)
class ACameraSampleCharacter : public ASpectatorPawn
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
public:
	ACameraSampleCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraZoomSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float MinCameraZoom = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float MaxCameraZoom = 2000.0f;


	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void ChangeCameraArmLength(float changeValue);
	void RotateCameraArm(FRotator rotation);
	void MoveCharacterForward(float changeValue);
	void MoveCharacterRight(float changeValue);
};

