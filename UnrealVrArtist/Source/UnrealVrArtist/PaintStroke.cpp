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
}

void APaintStroke::UpdatePaintStroke(FVector BrushLocation)
{
	auto Spline = CreateSplineMeshComponent();
	auto StartLocation = GetActorTransform().InverseTransformPosition(BrushLocation);
	auto EndLocation = GetActorTransform().InverseTransformPosition(LastBrushLocation);

	Spline->SetStartAndEnd(StartLocation, FVector::ZeroVector, EndLocation, FVector::ZeroVector);
	LastBrushLocation = BrushLocation;
}

USplineMeshComponent* APaintStroke::CreateSplineMeshComponent()
{
	auto Spline = NewObject<USplineMeshComponent>(this);
	Spline->SetMobility(EComponentMobility::Movable);
	Spline->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Spline->SetStaticMesh(SplineStaticMesh);
	Spline->SetMaterial(0, SplineMaterialInterface);
	Spline->RegisterComponent();

	return Spline;
}
