// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VRArtistSaveGame.generated.h"

USTRUCT()
struct FPaintStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class APaintStroke> Class;

	UPROPERTY()
	TArray<FVector> ControlPoints;
};

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
	static UVRArtistSaveGame* Load(FString SlotName);
	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }
	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);
	FString GetSlotName() const { return SlotName; }

protected:
	UPROPERTY()
	FString State;

	UPROPERTY()
	TArray<FPaintStrokeState> PaintStrokes;

	UPROPERTY()
	FString SlotName;

private:
	void ClearWorld(UWorld* World);
};
