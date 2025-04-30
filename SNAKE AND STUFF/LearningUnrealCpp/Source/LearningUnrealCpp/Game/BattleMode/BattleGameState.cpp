// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameState.h"

TArray<ARollaBallPlayer*> ABattleGameState::GetPlayersLeft()
{
	return PlayersLeft;
}

void ABattleGameState::AddPlayer(ARollaBallPlayer* _Player)
{
	for (auto Player : PlayersLeft)
	{
		if (Player == _Player) return;
	}
	PlayersLeft.Add(_Player);
}

void ABattleGameState::RemovePlayer(ARollaBallPlayer* Player)
{
	PlayersLeft.Remove(Player);
}

TArray<ULocalPlayer*> ABattleGameState::GetLocalPlayers()
{
	return LocalPlayers;
}

void ABattleGameState::AddLocalPlayer(ULocalPlayer* LocalPlayer)
{
	for (auto Player : LocalPlayers)
		if (Player == LocalPlayer) return;

	LocalPlayers.Add(LocalPlayer);
}

void ABattleGameState::RemoveAllLocalPlayers()
{
	for (auto Player : LocalPlayers)
		LocalPlayers.Remove(Player);
}
