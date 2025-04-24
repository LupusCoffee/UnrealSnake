// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"

//Begin play
//do this on a "HighScorePlayerState" class
//find the high score game state, set it to the "game state"
//do this on a "BattlePlayerState" class
//find the battle game state, set it to the "game state"

void APlayerStateBase::SetLengthScore(int NewLengthScore)
{
}

void APlayerStateBase::AddLengthScore(int Increment)
{
}

void APlayerStateBase::SetDeathStatus(bool DeathStatus)
{
	IsDead = DeathStatus;

	if (IsDead)
	{
		//invoke this player to be dead
		//game state created the event, game mode listens to it

		//do this on a "HighScorePlayerState" class
		//HighScoreGameState->OnPlayerDeathEvent.Broadcast(player);

		//do this on a "BattlePlayerState" class
		//find the battle game state, then do BattleGameState->OnPlayerDeathEvent.Broadcast(player);

		//the two types of player state will inherit from THIS class!
	}
	
	//->BATTLE GAME MODE: game state tells game mode (by listening)
	//  that a specific player has died (if 1 or less players left, end game)
	
	//->HIGH SCORE GAME MODE: game state tells game mode (by listening)
	//	that a specific player has died (respawns this
	//	RollaBallPlayer after 5 seconds with less score than previous)
}

int APlayerStateBase::GetLengthScore()
{
	return LengthScore;
}

bool APlayerStateBase::GetDeathStatus()
{
	return IsDead;
}
