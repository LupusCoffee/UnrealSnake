// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAiController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LearningUnrealCpp/Game/BattleMode/BattleGameState.h"
#include "LearningUnrealCpp/Game/BattleMode/BattlePlayerState.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScorePlayerState.h"
#include "LearningUnrealCpp/Items/RollaBallItemBase.h"


ASnakeAiController::ASnakeAiController(): AIPlayer(nullptr), BehaviorTree(nullptr), HighScoreGameState(nullptr),
                                          BattleGameState(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakeAiController::BeginPlay()
{
	Super::BeginPlay();

	//RunBehaviorTree(BehaviorTree); //tried doing it, didn't work. no time now. grrrrrrrrrr

	if (AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(GetWorld()))
	{
		HighScoreGameState = Cast<AHighScoreGameState>(GameStateBase);
		BattleGameState = Cast<ABattleGameState>(GameStateBase);
	}
}

void ASnakeAiController::InitializeCustomPlayerState()
{
	InitPlayerState();
	
	AIPlayer = GetPawn<ARollaBallPlayer>();
	if (!AIPlayer) return;

	AHighScorePlayerState* AIHighScorePlayerState = GetPlayerState<AHighScorePlayerState>();
	if (AIHighScorePlayerState)
	{
		AIHighScorePlayerState->SetPlayerPawn(AIPlayer);
		AIPlayer->SetPlayerState(AIHighScorePlayerState);
	}
	
	ABattlePlayerState* AIBattlePlayerState = GetPlayerState<ABattlePlayerState>();
	if (AIBattlePlayerState)
	{
		AIBattlePlayerState->SetPlayerPawn(AIPlayer);
		AIPlayer->SetPlayerState(AIBattlePlayerState);
	}
}

void ASnakeAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AIPlayer = GetPawn<ARollaBallPlayer>();
	if (!AIPlayer) return;

	if (rand() % 100 < 1) AIPlayer->MoveForward(10);
	if (rand() % 100 < 1) AIPlayer->Jump();
	
	switch (CurrentState)
	{
		case AIState::LOCATE_GATE:
			ClosestGateLocation = FVector(0,0,1000000000000000);
			if (HighScoreGameState)
			{
				for (auto Gate : HighScoreGameState->GetAllGates())
				{
					if (Gate->GetCurrentCooldown() > 0) continue;
					
					if ((AIPlayer->GetActorLocation() - Gate->GetActorLocation()).Length() < (AIPlayer->GetActorLocation() - ClosestGateLocation).Length())
						ClosestGateLocation = Gate->GetActorLocation();
				}
				if (HighScoreGameState->GetAllGates().Num() > 0)
					CurrentState = AIState::MOVE;
			}
			if (BattleGameState)
			{
				for (auto Gate : BattleGameState->GetAllGates())
				{
					if (Gate->GetCurrentCooldown() > 0) continue;
					
					if ((AIPlayer->GetActorLocation() - Gate->GetActorLocation()).Length() < (AIPlayer->GetActorLocation() - ClosestGateLocation).Length())
						ClosestGateLocation = Gate->GetActorLocation();
				}
				if (BattleGameState->GetAllGates().Num() > 0)
					CurrentState = AIState::MOVE;
			}
			break;
		
		case AIState::MOVE:
			//rotate towards goal
			FRotator GoalRotation = (ClosestGateLocation - AIPlayer->GetActorLocation()).ToOrientationRotator();
			if (AIPlayer->GetRotation().Yaw < GoalRotation.Yaw - RadiusAroundGoalRotation) AIPlayer->RotateCamera(1);
			else if (AIPlayer->GetRotation().Yaw > GoalRotation.Yaw + RadiusAroundGoalRotation) AIPlayer->RotateCamera(-1);
			//move forward
			else
			{
				float DistanceFromGoal = (ClosestGateLocation - AIPlayer->GetActorLocation()).Length();
				if (DistanceFromGoal > GoalRadius) AIPlayer->MoveForward(1);
				else CurrentState = AIState::LOCATE_GATE;
			}
			break;
	}
}

