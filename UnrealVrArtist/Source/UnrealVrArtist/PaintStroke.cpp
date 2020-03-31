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
	if (LastBrushLocation.IsNearlyZero())
	{
		LastBrushLocation = BrushLocation;
		return;
	}

	PaintStrokeMeshes->AddInstance(GetNextSegmentTransform(BrushLocation));

	LastBrushLocation = BrushLocation;
}

FTransform APaintStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));

	return SegmentTransform;
}

FVector APaintStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - LastBrushLocation;
	return FVector(Segment.Size(), 1, 1);
}

FQuat APaintStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - LastBrushLocation;
	FVector SegmentNormal = Segment.GetSafeNormal();
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentNormal);
}

FVector APaintStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	return GetTransform().InverseTransformPosition(LastBrushLocation);
}
