// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAiController.h"

#include "LearningUnrealCpp/Game/BattleMode/BattlePlayerState.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScorePlayerState.h"


ASnakeAiController::ASnakeAiController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakeAiController::BeginPlay()
{
	Super::BeginPlay();

	//InitializeCustomPlayerState();
}

void ASnakeAiController::InitializeCustomPlayerState()
{
	InitPlayerState();
	
	ARollaBallPlayer* AIPlayer = GetPawn<ARollaBallPlayer>();
	if (!AIPlayer) return;

	AHighScorePlayerState* AIHighScorePlayerState = GetPlayerState<AHighScorePlayerState>();
	if (AIHighScorePlayerState)
	{
		AIHighScorePlayerState->SetPlayerPawn(AIPlayer);
		AIPlayer->SetPlayerState(AIHighScorePlayerState);
	}
	
	ABattlePlayerState* AIBattlePlayerState = GetPlayerState<ABattlePlayerState>();
	if (AIBattlePlayerState)
	{
		AIBattlePlayerState->SetPlayerPawn(AIPlayer);
		AIPlayer->SetPlayerState(AIBattlePlayerState);
	}
}

void ASnakeAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

