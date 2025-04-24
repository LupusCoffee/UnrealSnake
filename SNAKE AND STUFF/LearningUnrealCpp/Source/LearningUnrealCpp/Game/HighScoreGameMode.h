// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGameModeBase.h"
#include "HighScoreGameMode.generated.h"

UCLASS()
class LEARNINGUNREALCPP_API AHighScoreGameMode : public ASnakeGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION()
	virtual void PlayerDeath(ARollaBallPlayer* PlayerActor) override;
};
