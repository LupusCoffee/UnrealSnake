// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RollaBallPlayer.h"
#include "GameFramework/GameStateBase.h"
#include "HighScoreGameState.generated.h"

	//->HIGH SCORE GAME MODE: game state tells game mode (by listening)
	//	that a specific player has died (respawns this
	//	RollaBallPlayer after 5 seconds with less score than previous)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathEvent, ARollaBallPlayer*, PlayerActor);

UCLASS()
class LEARNINGUNREALCPP_API AHighScoreGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerDeathEvent OnPlayerDeathEvent;
};
