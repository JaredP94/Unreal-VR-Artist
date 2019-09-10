// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintStroke.generated.h"

UCLASS()
class UNREALVRARTIST_API APaintStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintStroke();

	void UpdatePaintStroke(FVector BrushLocation);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* SplineStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* SplineMaterialInterface;

private:
	class USplineMeshComponent* CreateSplineMeshComponent();

	FVector LastBrushLocation;
};
