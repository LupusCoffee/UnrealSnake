// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeNodeMoveForward.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"


void USnakeNodeMoveForward::RunTask(ARollaBallPlayer* SnakePlayerAI, FVector GoalLocation)

{
	if (SnakePlayerAI) SnakePlayerAI->MoveForward(1);

	int DistanceFromGoal = (SnakePlayerAI->GetActorLocation() - GoalLocation).Length();
	
	if (DistanceFromGoal < GoalRadius) FinishExecute(true);
	else FinishExecute(false);
}
