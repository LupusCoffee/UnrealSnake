// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameInstance.h"

class ARollaBallPlayer;


int USnakeGameInstance::GetHighestScore()
{
	return HighestScore;
}

FString USnakeGameInstance::GetWinningPlayerName()
{
	return WinningPlayerName;
}

int USnakeGameInstance::GetAmountOfPlayers()
{
	return AmountOfPlayers;
}

void USnakeGameInstance::SetHighestScore(int Score)
{
	HighestScore = Score;
}

void USnakeGameInstance::SetWinningPlayerName(FString Name)
{
	WinningPlayerName = Name;
}

void USnakeGameInstance::ResetHighScore()
{
	HighestScore = DefaultHighestScore;
}
