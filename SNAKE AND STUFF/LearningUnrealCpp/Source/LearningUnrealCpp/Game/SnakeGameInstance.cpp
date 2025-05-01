// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

int USnakeGameInstance::GetAmountOfAi()
{
	return AmountOfAi;
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

void USnakeGameInstance::PlayGame(bool IsHighScoreMode, FString MapNum, int PlayerAmount, int AiAmount)
{
	AmountOfPlayers = PlayerAmount;
	AmountOfAi = AiAmount;
	
	if (IsHighScoreMode) UGameplayStatics::OpenLevel(this, FName("HighScoreMap" + MapNum));
	else UGameplayStatics::OpenLevel(this, FName("BattleMap" + MapNum));
}
