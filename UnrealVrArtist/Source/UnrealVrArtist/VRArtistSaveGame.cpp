// Fill out your copyright notice in the Description page of Project Settings.


#include "VRArtistSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"

#include "PainterSaveGameIndex.h"
#include "PaintStroke.h"

UVRArtistSaveGame* UVRArtistSaveGame::Create()
{
	UVRArtistSaveGame* NewSaveGame = Cast<UVRArtistSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();

	if (!NewSaveGame->Save()) return nullptr;

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();

	return NewSaveGame;
}

bool UVRArtistSaveGame::Save()
{
	UE_LOG(LogTemp, Warning, TEXT("Painting Index:"));

	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		UE_LOG(LogTemp, Warning, TEXT("Painting name: %s"), *SlotName);
	}

	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UVRArtistSaveGame* UVRArtistSaveGame::Load(FString SlotName)
{
	return Cast<UVRArtistSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UVRArtistSaveGame::SerializeFromWorld(UWorld* World)
{
	PaintStrokes.Empty();
	for (TActorIterator<APaintStroke> PaintStrokeItr(World); PaintStrokeItr; ++PaintStrokeItr)
	{
		PaintStrokes.Add(PaintStrokeItr->SerializeToStruct());
	}
}

void UVRArtistSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);
	for (FPaintStrokeState PaintStrokeState : PaintStrokes)
	{
		APaintStroke::SpawnAndDeserializeFromStruct(World, PaintStrokeState);
	}
}

void UVRArtistSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<APaintStroke> PaintStrokeItr(World); PaintStrokeItr; ++PaintStrokeItr)
	{
		PaintStrokeItr->Destroy();
	}
}
