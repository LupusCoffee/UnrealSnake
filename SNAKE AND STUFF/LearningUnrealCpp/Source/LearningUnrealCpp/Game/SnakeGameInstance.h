// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

class ARollaBallPlayer;

UCLASS()
class LEARNINGUNREALCPP_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	int DefaultHighestScore = 0;
	int HighestScore;
	FString WinningPlayerName;
	UPROPERTY(EditDefaultsOnly) int AmountOfPlayers = 1;
	UPROPERTY(EditDefaultsOnly) int AmountOfAi = 0;

public:
	UFUNCTION(BlueprintCallable) int GetHighestScore();
	UFUNCTION(BlueprintCallable) FString GetWinningPlayerName();
	UFUNCTION(BlueprintCallable) int GetAmountOfPlayers();
	UFUNCTION(BlueprintCallable) int GetAmountOfAi();

	UFUNCTION() void SetHighestScore(int Score);
	UFUNCTION() void SetWinningPlayerName(FString Name);

	UFUNCTION() void ResetHighScore();

	UFUNCTION(BlueprintCallable)
	void PlayGame(bool IsHighScoreMode, FString MapNum, int PlayerAmount, int AiAmount);
};
