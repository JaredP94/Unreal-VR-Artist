// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VRArtistSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVRARTIST_API UVRArtistSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	static UVRArtistSaveGame* Create();
	bool Save();
	static UVRArtistSaveGame* Load();
	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }
	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

protected:
	UPROPERTY()
	FString State;

	UPROPERTY()
	TArray<TSubclassOf<class APaintStroke>> PaintStrokes;

private:
	void ClearWorld(UWorld* World);
};
