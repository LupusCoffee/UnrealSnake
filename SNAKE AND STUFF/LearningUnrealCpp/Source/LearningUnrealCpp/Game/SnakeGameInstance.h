// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	int HighestScore;
	UPROPERTY() ARollaBallPlayer* WinningPlayer;

public:
	UFUNCTION() void SetHighestScore(int Score);
	UFUNCTION() void SetWinningPlayer(ARollaBallPlayer* Player);
	UFUNCTION(BlueprintCallable) int GetHighestScore();
	UFUNCTION(BlueprintCallable) ARollaBallPlayer* GetWinningPlayer();
};
