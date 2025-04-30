// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreGameMode.h"
#include "HighScoreGameState.h"
#include "HighScorePlayerState.h"
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
	if (HighScoreGameState)
	{
		HighScoreGameState->SetCurrentTime(HighScoreGameState->GetGameLength()); //maybe make a seperate function in game state for this lol
		HighScoreGameState->OnPlayerSpawn.AddDynamic(this, &ThisClass::PlayerSpawned);
		HighScoreGameState->OnPlayerDeathEvent.AddDynamic(this, &ThisClass::PlayerDeath);
		HighScoreGameState->OnPlayerGotPoints.AddDynamic(this, &ThisClass::AHighScoreGameMode::PlayerGotPoints);
	}

	//Game instance stuff
	if (GameInstance) GameInstance->ResetHighScore();
}


void AHighScoreGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!HighScoreGameState) return;

	//tick respawn time for players that need respawning
	HighScoreGameState->PlayersRespawnTick(DeltaTime);

	//TODO: put this into a function of its own
	//End Game
	HighScoreGameState->SetCurrentTime(HighScoreGameState->GetCurrentTime() - DeltaTime);
	if (HighScoreGameState->GetCurrentTime() < 0)
	{
		//TODO: set state to outro
		
		if (GameInstance)
		{
			//Set winning player and their score
			GameInstance->SetHighestScore(HighScoreGameState->GetHighestScore());
			ARollaBallPlayer* WinningPlayer = HighScoreGameState->GetWinningPlayer();
			if (WinningPlayer) GameInstance->SetWinningPlayerName(WinningPlayer->GetName());

			//Remove all players - although, doesn't include the first player.... hmnmmmmmm
			for (auto _LocalPlayer : HighScoreGameState->GetLocalPlayers())
				GameInstance->RemoveLocalPlayer(_LocalPlayer);
			HighScoreGameState->RemoveAllLocalPlayers();
			for (auto Player : HighScoreGameState->GetCurrentPlayers())
			{
				HighScoreGameState->RemoveCurrentPlayer(Player);
				Player->Destroy();
			}

			//Switch map
			UGameplayStatics::OpenLevel(GameInstance, FName(TEXT("HighScoreResults"))); //TODO: use an enum for map names
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
				TEXT("NO HIGH SCORE GAME INSTANCE."));
		}
	}
	
	//TODO: update a widget for all players to see the timer
}

void AHighScoreGameMode::SpawnPlayers()
{
	//TODO: delay a bit before each creation
	if (GameInstance && GameInstance->GetAmountOfPlayers() > 1)
	{
		for (int i = 0; i < GameInstance->GetAmountOfPlayers()-1; i++)
		{
			FString Test = FString("Test");
			ULocalPlayer* LocalPlayer = GameInstance->CreateLocalPlayer(-1, Test, true);

			//ugh
			if (!LocalPlayer) break;
			if (HighScoreGameState) HighScoreGameState->AddLocalPlayer(LocalPlayer);
			
			AHighScorePlayerState* PlayerState = LocalPlayer->GetPlayerController(GetWorld())->GetPlayerState<AHighScorePlayerState>();
			if (!PlayerState) break;

			ARollaBallPlayer* PlayerActor = nullptr;
			APawn* PlayerPawn = LocalPlayer->GetPlayerController(GetWorld())->GetPawn();
			if (PlayerPawn) PlayerActor = Cast<ARollaBallPlayer>(PlayerPawn);
			if (PlayerActor) PlayerState->SetPlayerPawn(PlayerActor);
		}
	}
}

//Bound Functions
void AHighScoreGameMode::PlayerSpawned(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerSpawned(PlayerActor);
	
	if (PlayerActor && HighScoreGameState)
		HighScoreGameState->AddCurrentPlayer(PlayerActor);

	//TODO: set name
}

void AHighScoreGameMode::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerDeath(PlayerActor);
	
	if (!HighScoreGameState) return;
	
	HighScoreGameState->AddPlayerToRespawn(PlayerActor->GetController(), PlayerActor->GetClass());

	//Destroy
	HighScoreGameState->RemoveCurrentPlayer(PlayerActor);
	PlayerActor->Destroy();
}

void AHighScoreGameMode::PlayerGotPoints(ARollaBallPlayer* PlayerActor, int Score)
{
	if (HighScoreGameState->GetHighestScore() < Score)
	{
		HighScoreGameState->SetWinningPlayer(PlayerActor);
		HighScoreGameState->SetHighestScore(Score);
	}
}
