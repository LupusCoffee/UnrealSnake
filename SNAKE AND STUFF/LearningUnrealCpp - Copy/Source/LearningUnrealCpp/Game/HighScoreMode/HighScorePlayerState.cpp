// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScorePlayerState.h"

#include "Kismet/GameplayStatics.h"

class AGameState;

void AHighScorePlayerState::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	if (GameState) HighScoreGameState = Cast<AHighScoreGameState>(GameState);
	
	if (GetPawn()) PlayerPawn = Cast<ARollaBallPlayer>(GetPawn()); //hmmmmmmmmm

	//bindings
	if (HighScoreGameState)
		HighScoreGameState->OnPlayerGotPoints.AddDynamic(this, &AHighScorePlayerState::SetLengthScore);
}

int AHighScorePlayerState::GetLengthScore()
{
	return LengthScore;
}

void AHighScorePlayerState::SetLengthScore(ARollaBallPlayer* Player, int NewLengthScore)
{
	LengthScore = NewLengthScore;
}

void AHighScorePlayerState::SetDeathStatus(bool DeathStatus)
{
	Super::SetDeathStatus(DeathStatus);

	if (!DeathStatus) return;
	if (PlayerPawn && HighScoreGameState)
		HighScoreGameState->OnPlayerDeathEvent.Broadcast(PlayerPawn);
}

void AHighScorePlayerState::SetPlayerPawn(ARollaBallPlayer* Pawn)
{
	if (GetPawn()) PlayerPawn = Cast<ARollaBallPlayer>(GetPawn());
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "NO PLAYER PAWN");
		PlayerPawn = Pawn;
	}
}
