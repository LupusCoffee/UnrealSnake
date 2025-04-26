// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SnakeGameModeBase.h"
#include "HighScoreGameMode.generated.h"

class USnakeGameInstance;
class AHighScoreGameState;

UCLASS()
class LEARNINGUNREALCPP_API AHighScoreGameMode : public ASnakeGameModeBase
{
	GENERATED_BODY()

public:
	AHighScoreGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY()
	AHighScoreGameState* HighScoreGameState;
	
	UFUNCTION()
	void PlayerGotPoints(ARollaBallPlayer* PlayerActor, int Score);
	UFUNCTION()
	virtual void PlayerDeath(ARollaBallPlayer* PlayerActor) override;
	
};
