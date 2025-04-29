// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleGameState.generated.h"

class ARollaBallPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSpawnEvent, ARollaBallPlayer*, PlayerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathEvent, ARollaBallPlayer*, PlayerActor);

UCLASS()
class LEARNINGUNREALCPP_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<ARollaBallPlayer*> PlayersLeft;

public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerSpawnEvent OnPlayerSpawn;
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerDeathEvent OnPlayerDeathEvent;

public:
	UFUNCTION()
	TArray<ARollaBallPlayer*> GetPlayersLeft();
	UFUNCTION()
	void AddPlayer(ARollaBallPlayer* _Player);
	UFUNCTION()
	void RemovePlayer(ARollaBallPlayer* _Player);
};
