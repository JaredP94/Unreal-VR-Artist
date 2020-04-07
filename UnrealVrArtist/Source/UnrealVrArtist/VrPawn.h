// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "HandControllerBase.h"

#include "VrPawn.generated.h"

UCLASS()
class UNREALVRARTIST_API AVrPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVrPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* VrRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* VrCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right Hand Controller")
	AHandControllerBase* RightHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left Hand Controller")
	AHandControllerBase* LeftHandController;

	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.5;

private:
	void RightMotionTriggerPressed();
	void RightMotionTriggerReleased();
	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurrentPage(int32 Offset);

private:
	// State
	int32 LastPaginationOffset = 0;
};
