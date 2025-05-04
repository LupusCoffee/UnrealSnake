// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeNodeRotateTowardsGoal.h"

#include "LearningUnrealCpp/Game/RollaBallPlayer.h"

void USnakeNodeRotateTowardsGoal::RunTask(ARollaBallPlayer* SnakePlayerAI, FVector GoalLocation)
{
	if (SnakePlayerAI) SnakePlayerAI->RotateCamera(1);

	FRotator GoalRotation = (GoalLocation - SnakePlayerAI->GetActorLocation()).ToOrientationRotator();
	FRotator RotationDelta = (SnakePlayerAI->GetActorRotation() - GoalRotation);
	
	if (RotationDelta.Vector().Length() < RadiusAroundGoalRotation) FinishExecute(true);
	else FinishExecute(false);
}
