// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "BattleGameState.h"
#include "BattlePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "LearningUnrealCpp/Game/SnakeGameInstance.h"
#include "LearningUnrealCpp/Game/StateControllerGameInstanceSubsystem.h"

class UStateControllerGameInstanceSubsystem;

ABattleGameMode::ABattleGameMode(): BattleGameState(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	BattleGameState = GetGameState<ABattleGameState>();
	if (BattleGameState)
	{
		BattleGameState->OnPlayerSpawn.AddDynamic(this, &ThisClass::PlayerSpawned);
		BattleGameState->OnPlayerDeathEvent.AddDynamic(this, &ThisClass::PlayerDeath);
	}
	
	if (!GameInstance) return;
	UStateControllerGameInstanceSubsystem* StateController =
		GameInstance->GetSubsystem<UStateControllerGameInstanceSubsystem>();
	if (!StateController) return;
	StateController->SetState(ESkibidiState::BATTLE);
}

void ABattleGameMode::SpawnPlayers()
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
			if (BattleGameState) BattleGameState->AddLocalPlayer(LocalPlayer);
			
			ABattlePlayerState* PlayerState = LocalPlayer->GetPlayerController(GetWorld())->GetPlayerState<ABattlePlayerState>();
			if (!PlayerState) break;

			ARollaBallPlayer* PlayerActor = nullptr;
			APawn* PlayerPawn = LocalPlayer->GetPlayerController(GetWorld())->GetPawn();
			if (PlayerPawn) PlayerActor = Cast<ARollaBallPlayer>(PlayerPawn);
			if (PlayerActor) PlayerState->SetPlayerPawn(PlayerActor);
		}
	}
}

//Bound Functions
void ABattleGameMode::PlayerSpawned(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerSpawned(PlayerActor);

	if (PlayerActor && BattleGameState)
		BattleGameState->AddPlayer(PlayerActor);

	//TODO: set name
}

void ABattleGameMode::PlayerDeath(ARollaBallPlayer* PlayerActor)
{
	Super::PlayerDeath(PlayerActor);

	if (!BattleGameState) return;

	BattleGameState->RemovePlayer(PlayerActor);
	PlayerActor->Destroy();

	//Check to end game + end game if needed - THERE SHOULD BE A FUNCTION FOR THIS BUT AAAAAAAAAAHHHHHHHHHHHHHHHH
	if (BattleGameState->GetPlayersLeft().Num() <= 1)
	{
		if (!GameInstance) return;

		//remove all local player
		for (auto _LocalPlayer : BattleGameState->GetLocalPlayers())
			GameInstance->RemoveLocalPlayer(_LocalPlayer);
		BattleGameState->RemoveAllLocalPlayers();
		
		if (BattleGameState->GetPlayersLeft().IsEmpty())
		{
			GameInstance->SetWinningPlayerName(TEXT("NONE NOPE NADA HAHAHAHA"));
			UGameplayStatics::OpenLevel(GameInstance, FName(TEXT("BattleResults"))); //TODO: use an enum for map names
		}
		else
		{
			GameInstance->SetWinningPlayerName(BattleGameState->GetPlayersLeft()[0]->GetName());
			for (auto Player : BattleGameState->GetPlayersLeft())
			{
				BattleGameState->RemovePlayer(Player);
				Player->Destroy();
			}
			UGameplayStatics::OpenLevel(GameInstance, FName(TEXT("BattleResults"))); //TODO: use an enum for map names
		}
	}
}
