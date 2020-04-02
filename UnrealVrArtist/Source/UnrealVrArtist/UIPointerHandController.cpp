// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandController.h"

#include "InputCoreTypes.h"


AUIPointerHandController::AUIPointerHandController()
{
	Pointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
	Pointer->SetupAttachment(GetRootComponent());
}


void AUIPointerHandController::MotionControllerTriggerPressed()
{
	Pointer->PressPointerKey(EKeys::LeftMouseButton);
}


void AUIPointerHandController::MotionControllerTriggerReleased()
{
	Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
}