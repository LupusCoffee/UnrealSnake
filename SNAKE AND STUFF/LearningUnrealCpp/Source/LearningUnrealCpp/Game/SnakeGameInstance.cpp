// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameInstance.h"

void USnakeGameInstance::SetHighestScore(int Score)
{
	HighestScore = Score;
}

void USnakeGameInstance::SetWinningPlayer(ARollaBallPlayer* Player)
{
	WinningPlayer = Player;
}

int USnakeGameInstance::GetHighestScore()
{
	return HighestScore;
}

ARollaBallPlayer* USnakeGameInstance::GetWinningPlayer()
{
	return WinningPlayer;
}
