// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "VRArtistSaveGame.h"

#include "PainterSaveGameIndex.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVRARTIST_API UPainterSaveGameIndex : public USaveGame
{
	GENERATED_BODY()
	
public:
	static UPainterSaveGameIndex* Load();
	bool Save();

	void AddSaveGame(UVRArtistSaveGame* SaveGame);
	TArray<FString> GetSlotNames() const { return SlotNames; }

protected:
	UPROPERTY()
	TArray<FString> SlotNames;

private:
	static const FString SLOT_NAME;

};