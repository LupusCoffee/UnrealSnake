// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"
#include "LearningUnrealCpp/Game/Input/BaseMovementDataConfig.h"


void ASnakePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetupPlayer(InPawn);
}

void ASnakePlayerController::SetupPlayer(APawn* InPawn)
{
	if (InPawn) MyPlayer = Cast<ARollaBallPlayer>(InPawn);
	if (MyPlayer) SetupInput();
}

void ASnakePlayerController::SetupInput()
{
	if (!GetLocalPlayer()) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem) return;
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
	
	if (!MyPlayer->InputComponent) return;
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(MyPlayer->InputComponent);

	if (!Input) return;
	Input->BindAction(InputActions->CameraMovement, ETriggerEvent::Triggered, MyPlayer, "RotateCamera");
	Input->BindAction(InputActions->MoveRight, ETriggerEvent::Triggered, MyPlayer, "MoveRight");
	Input->BindAction(InputActions->MoveForward, ETriggerEvent::Triggered, MyPlayer, "MoveForward");
	Input->BindAction(InputActions->Jump, ETriggerEvent::Started, MyPlayer, "Jump");
}
