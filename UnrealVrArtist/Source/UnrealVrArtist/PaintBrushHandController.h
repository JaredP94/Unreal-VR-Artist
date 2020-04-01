// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class UNREALVRARTIST_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintBrushHandController();

	void MotionControllerTriggerPressed() override;
	void MotionControllerTriggerReleased() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APaintStroke> PaintStrokeClass;

private:
	class APaintStroke* CurrentPaintStroke;
};
