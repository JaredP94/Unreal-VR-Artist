// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintStroke.h"

#include "Engine/World.h"
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

	PaintJointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PaintJointMeshes"));
	PaintJointMeshes->SetupAttachment(Root);
}

void APaintStroke::UpdatePaintStroke(FVector BrushLocation)
{
	ControlPoints.Add(BrushLocation);

	if (LastBrushLocation.IsNearlyZero())
	{
		LastBrushLocation = BrushLocation;
		PaintJointMeshes->AddInstance(GetNextJointTransform(BrushLocation));
		return;
	}

	PaintStrokeMeshes->AddInstance(GetNextSegmentTransform(BrushLocation));
	PaintJointMeshes->AddInstance(GetNextJointTransform(BrushLocation));

	LastBrushLocation = BrushLocation;
}

FTransform APaintStroke::GetNextJointTransform(FVector BrushLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(BrushLocation));
	return JointTransform;
}

FTransform APaintStroke::GetNextSegmentTransform(FVector BrushLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(BrushLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(BrushLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(BrushLocation));

	return SegmentTransform;
}

FVector APaintStroke::GetNextSegmentScale(FVector BrushLocation) const
{
	FVector Segment = BrushLocation - LastBrushLocation;
	return FVector(Segment.Size(), 1, 1);
}

FQuat APaintStroke::GetNextSegmentRotation(FVector BrushLocation) const
{
	FVector Segment = BrushLocation - LastBrushLocation;
	FVector SegmentNormal = Segment.GetSafeNormal();
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentNormal);
}

FVector APaintStroke::GetNextSegmentLocation(FVector BrushLocation) const
{
	return GetTransform().InverseTransformPosition(LastBrushLocation);
}

FPaintStrokeState APaintStroke::SerializeToStruct() const
{
	FPaintStrokeState PaintStrokeState;
	PaintStrokeState.Class = GetClass();
	PaintStrokeState.ControlPoints = ControlPoints;
	return PaintStrokeState;
}

APaintStroke* APaintStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FPaintStrokeState& PaintStrokeState)
{
	APaintStroke* PaintStroke = World->SpawnActor<APaintStroke>(PaintStrokeState.Class);
	for (FVector ControlPoint : PaintStrokeState.ControlPoints)
	{
		PaintStroke->UpdatePaintStroke(ControlPoint);
	}
	return PaintStroke;
}
