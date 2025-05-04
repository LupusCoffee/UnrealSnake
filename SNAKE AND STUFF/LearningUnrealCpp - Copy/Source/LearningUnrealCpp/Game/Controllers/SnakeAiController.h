// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "SnakeAiController.generated.h"

class ABattleGameState;
class AHighScoreGameState;

UENUM(BlueprintType)
enum class AIState : uint8 {
	LOCATE_GATE,
	MOVE
};

UCLASS()
class LEARNINGUNREALCPP_API ASnakeAiController : public AAIController
{
	GENERATED_BODY()

public:
	ASnakeAiController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Variables
	UPROPERTY() ARollaBallPlayer* AIPlayer;
	UPROPERTY(EditDefaultsOnly) UBehaviorTree* BehaviorTree;
	UPROPERTY() AIState CurrentState = AIState::LOCATE_GATE;
	FVector ClosestGateLocation = FVector(0,0,1000000000);
	UPROPERTY()	AHighScoreGameState* HighScoreGameState;
	UPROPERTY()	ABattleGameState* BattleGameState;
	UPROPERTY(EditAnywhere) float RadiusAroundGoalRotation = 1;
	UPROPERTY(EditAnywhere) float GoalRadius = 10;

	//Functions
	
	

public:
	void InitializeCustomPlayerState();
};
