// Fill out your copyright notice in the Description page of Project Settings.


#include "OutroGameMode.h"
#include "SnakeGameInstance.h"
#include "StateControllerGameInstanceSubsystem.h"

class UStateControllerGameInstanceSubsystem;

void AOutroGameMode::BeginPlay()
{
	Super::BeginPlay();

	USnakeGameInstance* GameInstance = GetGameInstance<USnakeGameInstance>();
	if (!GameInstance) return;
	UStateControllerGameInstanceSubsystem* StateController =
		GameInstance->GetSubsystem<UStateControllerGameInstanceSubsystem>();
	if (!StateController) return;
	StateController->SetState(ESkibidiState::OUTRO);
}
