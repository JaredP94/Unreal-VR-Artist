// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintStroke.h"

// Sets default values
APaintStroke::APaintStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaintStroke::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintStroke::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

