// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScorePlayerState.h"

#include "Kismet/GameplayStatics.h"

class AGameState;

void AHighScorePlayerState::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	if (GameState) HighScoreGameState = Cast<AHighScoreGameState>(GameState);
	
	if (GetPawn()) PlayerPawn = Cast<ARollaBallPlayer>(GetPawn());
}

void AHighScorePlayerState::SetDeathStatus(bool DeathStatus)
{
	Super::SetDeathStatus(DeathStatus);

	if (!DeathStatus) return;
	if (PlayerPawn && HighScoreGameState)
		HighScoreGameState->OnPlayerDeathEvent.Broadcast(PlayerPawn);
}
