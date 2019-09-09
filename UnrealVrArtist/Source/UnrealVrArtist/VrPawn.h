// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VrPawn.generated.h"

UCLASS()
class UNREALVRARTIST_API AVrPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVrPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AVrController> MotionControllerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* VrRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* VrCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Controller")
	class AVrController* RightMotionController;

};
