// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "PaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVRARTIST_API UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPaintingName(FString PaintingName);
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SlotName;

};
