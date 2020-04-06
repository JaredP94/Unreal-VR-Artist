// Fill out your copyright notice in the Description page of Project Settings.


#include "VrPawn.h"

#include "PaintBrushHandController.h"
#include "VRArtistSaveGame.h"
#include "PaintingGameMode.h"

#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

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
		RightMotionController = GetWorld()->SpawnActor<AHandControllerBase>(MotionControllerClass);
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
	auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());

	if (!GameMode) return;

	GameMode->Save();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
