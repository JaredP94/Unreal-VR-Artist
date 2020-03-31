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
};
