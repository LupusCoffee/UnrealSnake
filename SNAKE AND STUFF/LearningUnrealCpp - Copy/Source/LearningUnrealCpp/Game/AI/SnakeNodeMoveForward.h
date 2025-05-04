// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "SnakeNodeMoveForward.generated.h"

class UBlackboardKeyType_Object;
class ARollaBallPlayer;
/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API USnakeNodeMoveForward : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere) FBlackboardKeySelector Goal;
	
	UPROPERTY(EditAnywhere)
	int GoalRadius;
	
	UFUNCTION(BlueprintCallable)
	void RunTask(ARollaBallPlayer* SnakePlayerAI, FVector GoalLocation);
};
