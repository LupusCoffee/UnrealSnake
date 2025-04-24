// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreGameMode.h"

#include "HighScoreGameState.h"

void AHighScoreGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetGameState<AHighScoreGameState>())
		GetGameState<AHighScoreGameState>()->OnPlayerDeathEvent.AddDynamic(this, &ThisClass::PlayerDeath);
}

void AHighScoreGameMode::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerDeath(PlayerActor);

	//do stuff
}
