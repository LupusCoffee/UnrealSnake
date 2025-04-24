// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameModeBase.h"
#include "PlayerStateBase.h"

void ASnakeGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	//do this on a "HighScoreGameMode" class
	//find the high score game state, set it to the "game state"
	//do this on a "BattleGameMode" class
	//find the battle game state, set it to the "game state"

	//the two types of game mode will inherit from THIS class!

	//then...
	//GameState->OnPlayerDeathEvent.AddDynamic(this, &ThisClass::PlayerDeath);
}

void ASnakeGameModeBase::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	//this implementation will be different depending on the game mode
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f,
		FColor::Red, TEXT("Player is dead!"));
}
