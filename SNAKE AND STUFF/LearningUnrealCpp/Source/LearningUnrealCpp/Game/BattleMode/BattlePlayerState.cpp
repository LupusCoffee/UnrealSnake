// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePlayerState.h"
#include "Kismet/GameplayStatics.h"

void ABattlePlayerState::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	if (GameState) HighScoreGameState = Cast<AHighScoreGameState>(GameState);
	
	if (GetPawn()) PlayerPawn = Cast<ARollaBallPlayer>(GetPawn()); //hmmmmmmmmm
}

void ABattlePlayerState::SetDeathStatus(bool DeathStatus)
{
	Super::SetDeathStatus(DeathStatus);

	if (!DeathStatus) return;
	if (PlayerPawn && HighScoreGameState)
		HighScoreGameState->OnPlayerDeathEvent.Broadcast(PlayerPawn);
}

void ABattlePlayerState::SetPlayerPawn(ARollaBallPlayer* Pawn)
{
	if (GetPawn()) PlayerPawn = Cast<ARollaBallPlayer>(GetPawn());
	else PlayerPawn = Pawn;
}
