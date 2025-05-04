// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "LearningUnrealCpp/Game/BattleMode/BattleGameState.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScoreGameState.h"
#include "LocateClosestValidGate.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API ULocateClosestValidGate : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY()	AHighScoreGameState* HighScoreGameState;
	UPROPERTY()	ABattleGameState* BattleGameState;

	UFUNCTION(BlueprintCallable)
	void StartTask();
	
	UFUNCTION(BlueprintCallable)
	FVector RunTask(FVector StartPosition);
};
