// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "SnakeGameInstance.h"
#include "StateControllerGameInstanceSubsystem.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstance) return;
	UStateControllerGameInstanceSubsystem* StateController =
		GameInstance->GetSubsystem<UStateControllerGameInstanceSubsystem>();
	if (!StateController) return;
	StateController->SetState(ESkibidiState::MENU);
}
