// Fill out your copyright notice in the Description page of Project Settings.


#include "VrPawn.h"

#include "VrController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

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
	
	if (MotionControllerClass)
	{
		RightMotionController = GetWorld()->SpawnActor<AVrController>(MotionControllerClass);
		RightMotionController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightMotionController->SetOwner(this);
	}
}

