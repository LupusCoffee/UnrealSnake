// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameModeBase.h"
#include "SnakeGameInstance.h"
#include "PlayerStateBase.h"

void ASnakeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<USnakeGameInstance>();
		
	//reset game instance stuff
	
	//todo: add death and stuff here instead of highscore and battle game modes > since it happens for both
}

void ASnakeGameModeBase::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	TEXT("A Player Died!"));
}

void ASnakeGameModeBase::PlayerSpawned(ARollaBallPlayer* PlayerActor)
{
	
}
