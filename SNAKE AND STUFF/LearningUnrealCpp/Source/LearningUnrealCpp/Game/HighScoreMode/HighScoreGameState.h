// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RollaBallPlayer.h"
#include "GameFramework/GameStateBase.h"
#include "HighScoreGameState.generated.h"

	//->HIGH SCORE GAME MODE: game state tells game mode (by listening)
	//	that a specific player has died (respawns this
	//	RollaBallPlayer after 5 seconds with less score than previous)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerGotPoints, ARollaBallPlayer*, PlayerActor, int, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathEvent, ARollaBallPlayer*, PlayerActor);

UCLASS()
class LEARNINGUNREALCPP_API AHighScoreGameState : public AGameStateBase
{
	GENERATED_BODY()
	

protected:
	int HighestScore;
	UPROPERTY()	ARollaBallPlayer* WinningPlayer;

	UPROPERTY(EditDefaultsOnly) float GameLength;
	float CurrentTime;
	UPROPERTY(EditDefaultsOnly) float RespawnTime;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerGotPoints OnPlayerGotPoints;
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerDeathEvent OnPlayerDeathEvent;

	UFUNCTION() int GetHighestScore();
	UFUNCTION() ARollaBallPlayer* GetWinningPlayer();
	UFUNCTION() float GetGameLength();
	UFUNCTION() float GetCurrentTime();
	UFUNCTION() float GetRespawnTime();
	
	UFUNCTION() void SetHighestScore(int Score);
	UFUNCTION()	void SetWinningPlayer(ARollaBallPlayer* Player);
	UFUNCTION()	void SetCurrentTime(float time);
};
