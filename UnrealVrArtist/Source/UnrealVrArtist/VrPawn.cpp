// Fill out your copyright notice in the Description page of Project Settings.


#include "VrPawn.h"

#include "PaintBrushHandController.h"
#include "VRArtistSaveGame.h"
#include "PaintingGameMode.h"
#include "PaintingPicker.h"

#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AVrPawn::AVrPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VrRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Root"));
	SetRootComponent(VrRoot);

	VrCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Camera"));
	VrCamera->SetupAttachment(VrRoot);
}

// Called when the game starts or when spawned
void AVrPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (RightHandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetHand(EControllerHand::Right);
		RightHandController->SetOwner(this);
	}

	if (LeftHandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetHand(EControllerHand::Left);
		LeftHandController->SetOwner(this);
	}
}

void AVrPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightMotionTrigger"), EInputEvent::IE_Pressed, this, &AVrPawn::RightMotionTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightMotionTrigger"), EInputEvent::IE_Released, this, &AVrPawn::RightMotionTriggerReleased);
	PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVrPawn::PaginateRightAxisInput);
}

void AVrPawn::RightMotionTriggerPressed()
{
	if (RightHandController == nullptr)
		return;

	RightHandController->MotionControllerTriggerPressed();
}

void AVrPawn::RightMotionTriggerReleased()
{
	if (RightHandController == nullptr)
		return;

	RightHandController->MotionControllerTriggerReleased();
}

void AVrPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThumbstickThreshold ? 1 : 0;
	PaginationOffset += AxisValue < -PaginationThumbstickThreshold ? -1 : 0;

	if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
	{
		UpdateCurrentPage(PaginationOffset);
	}

	LastPaginationOffset = PaginationOffset;
}

void AVrPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}
