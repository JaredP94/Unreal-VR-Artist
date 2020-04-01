// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintBrushHandController.h"

#include "MotionControllerComponent.h"
#include "Engine/World.h"

#include "PaintStroke.h"

// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
}

void APaintBrushHandController::MotionControllerTriggerPressed()
{
	CurrentPaintStroke = GetWorld()->SpawnActor<APaintStroke>(PaintStrokeClass);
	CurrentPaintStroke->SetActorLocation(GetActorLocation());
}

void APaintBrushHandController::MotionControllerTriggerReleased()
{
	CurrentPaintStroke = nullptr;
}

// Called when the game starts or when spawned
void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPaintStroke == nullptr)
		return;

	CurrentPaintStroke->UpdatePaintStroke(GetActorLocation());
}

