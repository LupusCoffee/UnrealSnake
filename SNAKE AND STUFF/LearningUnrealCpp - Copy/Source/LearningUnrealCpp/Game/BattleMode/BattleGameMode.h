// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningUnrealCpp/Game/SnakeGameModeBase.h"
#include "BattleGameMode.generated.h"

class ARollaBallItemBase;
class USnakeGameInstance;
class ABattleGameState;
/**
there's a "battle" game mode where players try to kill each other

the last standing player wins

when the game is done, the winning player is displayed

this game mode can only be won if there is more than one player
 */
UCLASS()
class LEARNINGUNREALCPP_API ABattleGameMode : public ASnakeGameModeBase
{
	GENERATED_BODY()

public:
	ABattleGameMode();
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY()
	ABattleGameState* BattleGameState;
	UPROPERTY(EditDefaultsOnly)
	UClass* SpawnedAIClass;

	UFUNCTION(BlueprintCallable)
	void SpawnPlayers();

	//Bound Functions
	UFUNCTION()
	virtual void PlayerSpawned(ARollaBallPlayer* PlayerActor) override;
	UFUNCTION()
	virtual void PlayerDeath(ARollaBallPlayer* PlayerActor) override;
	UFUNCTION()
	void GateCreated(ARollaBallItemBase* Gate);
};
