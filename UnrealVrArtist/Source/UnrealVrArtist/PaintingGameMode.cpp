// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"

#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "VRArtistSaveGame.h"


void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);
}

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();

	Load();

	UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingGameMode::Save()
{
	UVRArtistSaveGame* Painting = UVRArtistSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void APaintingGameMode::Load()
{
	UVRArtistSaveGame* Painting = UVRArtistSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
	}
}