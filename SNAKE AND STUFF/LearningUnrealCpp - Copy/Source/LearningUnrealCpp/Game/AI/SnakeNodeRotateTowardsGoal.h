// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "SnakeNodeRotateTowardsGoal.generated.h"

class ARollaBallPlayer;

UCLASS()
class LEARNINGUNREALCPP_API USnakeNodeRotateTowardsGoal : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int RadiusAroundGoalRotation;
	
	UFUNCTION(BlueprintCallable)
	void RunTask(ARollaBallPlayer* SnakePlayerAI, FVector GoalLocation);
};
