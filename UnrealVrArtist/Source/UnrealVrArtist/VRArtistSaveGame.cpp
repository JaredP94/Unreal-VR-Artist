// Fill out your copyright notice in the Description page of Project Settings.


#include "VRArtistSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "PaintStroke.h"

UVRArtistSaveGame* UVRArtistSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UVRArtistSaveGame>(NewSaveGame);
}

bool UVRArtistSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0);
}

UVRArtistSaveGame* UVRArtistSaveGame::Load()
{
	return Cast<UVRArtistSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Test"), 0));
}

void UVRArtistSaveGame::SerializeFromWorld(UWorld* World)
{
	PaintStrokes.Empty();
	for (TActorIterator<APaintStroke> PaintStrokeItr(World); PaintStrokeItr; ++PaintStrokeItr)
	{
		//TODO:Serialize
		PaintStrokes.Add(PaintStrokeItr->GetClass());
	}
}

void UVRArtistSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);
	for (TSubclassOf<APaintStroke> PaintStrokeClass : PaintStrokes)
	{
		World->SpawnActor<APaintStroke>(PaintStrokeClass);
	}
}

void UVRArtistSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<APaintStroke> PaintStrokeItr(World); PaintStrokeItr; ++PaintStrokeItr)
	{
		PaintStrokeItr->Destroy();
	}
}
