// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintStroke.h"

#include "Components/SplineMeshComponent.h"

// Sets default values
APaintStroke::APaintStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintStrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PaintStrokeMeshes"));
	PaintStrokeMeshes->SetupAttachment(Root);
}

void APaintStroke::UpdatePaintStroke(FVector BrushLocation)
{
	FTransform NewStrokeTransform;
	FVector LocalBrushLocation = GetTransform().InverseTransformPosition(BrushLocation);
	NewStrokeTransform.SetLocation(LocalBrushLocation);
	PaintStrokeMeshes->AddInstance(NewStrokeTransform);
	LastBrushLocation = BrushLocation;
}
