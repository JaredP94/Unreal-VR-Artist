// Fill out your copyright notice in the Description page of Project Settings.


#include "VRArtistSaveGame.h"

#include "Kismet/GameplayStatics.h"

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
