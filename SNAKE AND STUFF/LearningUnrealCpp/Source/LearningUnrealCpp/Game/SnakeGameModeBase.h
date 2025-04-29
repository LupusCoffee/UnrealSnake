// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RollaBallPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

class USnakeGameInstance;

UCLASS()
class LEARNINGUNREALCPP_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY()
	USnakeGameInstance* GameInstance;
	
	virtual void PlayerDeath(ARollaBallPlayer* PlayerActor);
	virtual void PlayerSpawned(ARollaBallPlayer* PlayerActor);
};
