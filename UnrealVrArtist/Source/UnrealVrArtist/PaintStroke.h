// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"

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

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* PaintStrokeMeshes;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* PaintJointMeshes;

private:
	FTransform GetNextJointTransform(FVector BrushLocation) const;
	FTransform GetNextSegmentTransform(FVector BrushLocation) const;
	FVector GetNextSegmentScale(FVector BrushLocation) const;
	FQuat GetNextSegmentRotation(FVector BrushLocation) const;
	FVector GetNextSegmentLocation(FVector BrushLocation) const;

private:
	FVector LastBrushLocation;
};
