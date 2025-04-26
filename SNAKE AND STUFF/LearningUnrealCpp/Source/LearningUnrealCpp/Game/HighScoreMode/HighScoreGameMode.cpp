// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreGameMode.h"

#include "HighScoreGameState.h"
#include "../SnakeGameInstance.h"
#include "Kismet/GameplayStatics.h"


AHighScoreGameMode::AHighScoreGameMode(): HighScoreGameState(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHighScoreGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HighScoreGameState = GetGameState<AHighScoreGameState>();
	HighScoreGameState->SetCurrentTime(HighScoreGameState->GetGameLength());
	if (HighScoreGameState)
	{
		HighScoreGameState->OnPlayerGotPoints.AddDynamic(this, &ThisClass::AHighScoreGameMode::PlayerGotPoints);
		HighScoreGameState->OnPlayerDeathEvent.AddDynamic(this, &ThisClass::PlayerDeath);
	}
}


void AHighScoreGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HighScoreGameState) return;
	HighScoreGameState->SetCurrentTime(HighScoreGameState->GetCurrentTime() - DeltaTime);
	if (HighScoreGameState->GetCurrentTime() < 0)
	{
		//TODO: do this shit instead:
		//- pause game
		//- show widget
		
		//TODO: set state to outro
		
		USnakeGameInstance* GameInstance = GetGameInstance<USnakeGameInstance>();
		if (GameInstance)
		{
			GameInstance->SetHighestScore(HighScoreGameState->GetHighestScore());
			GameInstance->SetWinningPlayer(HighScoreGameState->GetWinningPlayer());
			UGameplayStatics::OpenLevel(GameInstance, FName(TEXT("HighScoreResults"))); //TODO: use an enum for map names
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
				TEXT("NO HIGH SCORE GAME INSTANCE."));
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	FString::SanitizeFloat(HighScoreGameState->GetCurrentTime()));
	
	//TODO: update a widget for all players to see the timer
}

void AHighScoreGameMode::PlayerGotPoints(ARollaBallPlayer* PlayerActor, int Score)
{
	if (HighScoreGameState->GetHighestScore() < Score)
	{
		HighScoreGameState->SetWinningPlayer(PlayerActor);
		HighScoreGameState->SetHighestScore(Score);
	}
}

void AHighScoreGameMode::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerDeath(PlayerActor);

	//wait 5 seconds, respawn player
}
