// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreGameState.h"

#include "HeadMountedDisplayTypes.h"
#include "HighScorePlayerState.h"
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

TArray<ARollaBallPlayer*> AHighScoreGameState::GetCurrentPlayers()
{
	return CurrentPlayers;
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

void AHighScoreGameState::AddCurrentPlayer(ARollaBallPlayer* Player)
{
	if (!Player) return;
	
	for (auto CurrentPlayer : CurrentPlayers)
	{
		if (CurrentPlayer == Player) return;
	}
	CurrentPlayers.Add(Player);
}

void AHighScoreGameState::RemoveCurrentPlayer(ARollaBallPlayer* Player)
{
	if (Player) CurrentPlayers.Remove(Player);
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
	
	Respawnee.Controller->Possess(RespawneeActor);
	Respawnee.Controller->GetPlayerState<AHighScorePlayerState>()->SetPlayerPawn(RespawneeActor);
}

TArray<ULocalPlayer*> AHighScoreGameState::GetLocalPlayers()
{
	return LocalPlayers;
}

void AHighScoreGameState::AddLocalPlayer(ULocalPlayer* LocalPlayer)
{
	for (auto Player : LocalPlayers)
		if (Player == LocalPlayer) return;

	LocalPlayers.Add(LocalPlayer);
}

void AHighScoreGameState::RemoveAllLocalPlayers()
{
	for (auto Player : LocalPlayers)
		LocalPlayers.Remove(Player);
}

TArray<ARollaBallItemBase*> AHighScoreGameState::GetAllGates()
{
	return AllGates;
}

void AHighScoreGameState::AddGate(ARollaBallItemBase* Gate)
{
	for (auto _Gate : AllGates)
		if (_Gate == Gate) return;

	AllGates.Add(Gate);
}
