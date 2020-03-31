// Fill out your copyright notice in the Description page of Project Settings.


#include "VrPawn.h"

#include "VrController.h"
#include "VRArtistSaveGame.h"

#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"

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

void AVrPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightMotionTrigger"), EInputEvent::IE_Pressed, this, &AVrPawn::RightMotionTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightMotionTrigger"), EInputEvent::IE_Released, this, &AVrPawn::RightMotionTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVrPawn::Save);
	PlayerInputComponent->BindAction(TEXT("Load"), EInputEvent::IE_Released, this, &AVrPawn::Load);
}

void AVrPawn::RightMotionTriggerPressed()
{
	if (RightMotionController == nullptr)
		return;

	RightMotionController->MotionControllerTriggerPressed();
}

void AVrPawn::RightMotionTriggerReleased()
{
	if (RightMotionController == nullptr)
		return;

	RightMotionController->MotionControllerTriggerReleased();
}

void AVrPawn::Save()
{
	UVRArtistSaveGame* Artwork = UVRArtistSaveGame::Create();
	Artwork->SetState("Hello World!");
	Artwork->SerializeFromWorld(GetWorld());
	Artwork->Save();
}

void AVrPawn::Load()
{
	UVRArtistSaveGame* Artwork = UVRArtistSaveGame::Load();
	if (Artwork)
	{
		Artwork->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Artwork State %s"), *Artwork->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found"));
	}
}