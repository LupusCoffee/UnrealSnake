// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScoreGameState.h"
#include "BattleGameState.generated.h"

class ARollaBallPlayer;

UCLASS()
class LEARNINGUNREALCPP_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<ARollaBallPlayer*> PlayersLeft;
	UPROPERTY(VisibleAnywhere)
	TArray<ULocalPlayer*> LocalPlayers;
	UPROPERTY()
	TArray<ARollaBallItemBase*> AllGates;

public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerSpawnEvent OnPlayerSpawn;
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerDeathEvent OnPlayerDeathEvent;
	UPROPERTY(BlueprintAssignable, Category = "GateEvent")
	FGateCreated OnGateCreated;

public:
	UFUNCTION()
	TArray<ARollaBallPlayer*> GetPlayersLeft();
	UFUNCTION()
	void AddPlayer(ARollaBallPlayer* _Player);
	UFUNCTION()
	void RemovePlayer(ARollaBallPlayer* _Player);

	UFUNCTION() TArray<ULocalPlayer*> GetLocalPlayers();
	UFUNCTION() void AddLocalPlayer(ULocalPlayer* LocalPlayer);
	UFUNCTION() void RemoveAllLocalPlayers();

	UFUNCTION() TArray<ARollaBallItemBase*> GetAllGates();
	UFUNCTION() void AddGate(ARollaBallItemBase* Gate);
};
