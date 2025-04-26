// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreGameState.h"

int AHighScoreGameState::GetHighestScore()
{
	return HighestScore;
}

ARollaBallPlayer* AHighScoreGameState::GetWinningPlayer()
{
	return WinningPlayer;
}

float AHighScoreGameState::GetGameLength()
{
	return GameLength;
}

float AHighScoreGameState::GetCurrentTime()
{
	return CurrentTime;
}

float AHighScoreGameState::GetRespawnTime()
{
	return RespawnTime;
}

void AHighScoreGameState::SetHighestScore(int Score)
{
	HighestScore = Score;
}

void AHighScoreGameState::SetWinningPlayer(ARollaBallPlayer* Player)
{
	WinningPlayer = Player;
}

void AHighScoreGameState::SetCurrentTime(float time)
{
	CurrentTime = time;
}
