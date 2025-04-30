// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RollaBallPlayer.h"
#include "GameFramework/GameStateBase.h"
#include "HighScoreGameState.generated.h"

	//->HIGH SCORE GAME MODE: game state tells game mode (by listening)
	//	that a specific player has died (respawns this
	//	RollaBallPlayer after 5 seconds with less score than previous)



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSpawnEvent, ARollaBallPlayer*, PlayerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathEvent, ARollaBallPlayer*, PlayerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerGotPoints, ARollaBallPlayer*, PlayerActor, int, Score);

USTRUCT()
struct FPlayerToRespawn
{
	GENERATED_BODY()

public:
	UPROPERTY() AController* Controller;
	UPROPERTY() UClass* Class;
	float RespawnTime;
	
	FPlayerToRespawn()
	{
		Controller = nullptr;
		Class = nullptr;
		RespawnTime = 0;
	}
	FPlayerToRespawn(AController* _Controller, UClass* _Class, float _RespawnTime)
	{
		Controller = _Controller;
		Class = _Class;
		RespawnTime = _RespawnTime;
	}
	
	bool RespawnTick(float Increment)
	{
		if (RespawnTime > 0)
		{
			RespawnTime -= Increment;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
			FString::SanitizeFloat(RespawnTime));
			return false;
		}

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
			TEXT("Respawning Player"));
		return true;
	}
};

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
	UPROPERTY(EditDefaultsOnly) FVector RespawnLocation;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerSpawnEvent OnPlayerSpawn;
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerDeathEvent OnPlayerDeathEvent;
	UPROPERTY(BlueprintAssignable, Category = "PlayerEvents")
	FPlayerGotPoints OnPlayerGotPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<ARollaBallPlayer*> CurrentPlayers;
	UPROPERTY(VisibleAnywhere)
	TArray<ULocalPlayer*> LocalPlayers;
	UPROPERTY()
	TArray<FPlayerToRespawn> PlayersToRespawn;
	
	UFUNCTION() int GetHighestScore();
	UFUNCTION() ARollaBallPlayer* GetWinningPlayer();
	UFUNCTION() float GetGameLength();
	UFUNCTION() float GetCurrentTime();
	UFUNCTION() float GetRespawnTime();
	UFUNCTION() TArray<ARollaBallPlayer*> GetCurrentPlayers();
	UFUNCTION() TArray<FPlayerToRespawn> GetPlayersToRespawn();
	
	UFUNCTION() void SetHighestScore(int Score);
	UFUNCTION()	void SetWinningPlayer(ARollaBallPlayer* Player);
	UFUNCTION()	void SetCurrentTime(float time);
	UFUNCTION()	void AddCurrentPlayer(ARollaBallPlayer* Player);
	UFUNCTION()	void RemoveCurrentPlayer(ARollaBallPlayer* Player);
	UFUNCTION() void AddPlayerToRespawn(AController* Controller, UClass* Class);
	UFUNCTION() void PlayersRespawnTick(float DeltaTime);
	UFUNCTION() void RespawnPlayer(FPlayerToRespawn Respawnee);

	UFUNCTION() TArray<ULocalPlayer*> GetLocalPlayers();
	UFUNCTION() void AddLocalPlayer(ULocalPlayer* LocalPlayer);
	UFUNCTION() void RemoveAllLocalPlayers();
};
