// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTailComponent.h"

#include "Kismet/GameplayStatics.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScoreGameState.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScorePlayerState.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"


// Sets default values for this component's properties
UPlayerTailComponent::UPlayerTailComponent(): Player(nullptr), HighScoreGameState(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerTailComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ARollaBallPlayer>(GetOwner());
	
	if (AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(GetWorld()))
		HighScoreGameState = Cast<AHighScoreGameState>(GameStateBase);
}

void UPlayerTailComponent::AddTail()
{
	Super::AddTail();

	if (HighScoreGameState && Player)
		HighScoreGameState->OnPlayerGotPoints.Broadcast(Player, CurrentLength*10); //10 for fun lol, i know magic number, yada yada
}

