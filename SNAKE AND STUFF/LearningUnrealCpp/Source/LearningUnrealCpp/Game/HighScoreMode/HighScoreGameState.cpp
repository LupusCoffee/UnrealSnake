// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreGameState.h"

#include "GameFramework/Character.h"

int AHighScoreGameState::GetHighestScore()
{
	return HighestScore;
}

ARollaBallPlayer* AHighScoreGameState::GetWinningPlayer()
{
	return WinningPlayer;
}

float AHighScoreGameState::GetGameLength()
{
	return GameLength;
}

float AHighScoreGameState::GetCurrentTime()
{
	return CurrentTime;
}

float AHighScoreGameState::GetRespawnTime()
{
	return RespawnTime;
}

TArray<FPlayerToRespawn> AHighScoreGameState::GetPlayersToRespawn()
{
	return PlayersToRespawn;
}

void AHighScoreGameState::SetHighestScore(int Score)
{
	HighestScore = Score;
}

void AHighScoreGameState::SetWinningPlayer(ARollaBallPlayer* Player)
{
	WinningPlayer = Player;
}

void AHighScoreGameState::SetCurrentTime(float time)
{
	CurrentTime = time;
}

void AHighScoreGameState::AddPlayerToRespawn(AController* Controller, UClass* Class)
{
	for (auto Player : PlayersToRespawn)
		if (Player.Controller == Controller) return;

	PlayersToRespawn.Add(FPlayerToRespawn(Controller, Class, RespawnTime));
}

//should these functions below be in the game mode class?
//As long as there are players to respawn, tick respawn time then respawn
void AHighScoreGameState::PlayersRespawnTick(float DeltaTime)
{
	for (int i = 0; i < PlayersToRespawn.Num(); i++)
	{
		if (PlayersToRespawn[i].RespawnTick(DeltaTime))
		{			
			RespawnPlayer(PlayersToRespawn[i]);
			PlayersToRespawn.RemoveAt(i);
		}
	}
}

void AHighScoreGameState::RespawnPlayer(FPlayerToRespawn Respawnee)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ARollaBallPlayer* RespawneeActor = GetWorld()->SpawnActor<ARollaBallPlayer>
	(
		Respawnee.Class,
		RespawnLocation,
		FRotator::ZeroRotator,
		SpawnParameters	
	);

	//RespawneeActor->Execute_GetTailComponent(RespawneeActor)->AddTail();
	
	Respawnee.Controller->Possess(RespawneeActor);
}
