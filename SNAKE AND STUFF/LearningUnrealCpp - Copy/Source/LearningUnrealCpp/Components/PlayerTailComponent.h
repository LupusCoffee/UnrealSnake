// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tail_Component.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScoreGameState.h"
#include "PlayerTailComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEARNINGUNREALCPP_API UPlayerTailComponent : public UTail_Component
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerTailComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	ARollaBallPlayer* Player;
	UPROPERTY()
	AHighScoreGameState* HighScoreGameState;

public:
	virtual void AddTail() override;
};
