// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreGameState.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API APlayerStateBase : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere)
	int LengthScore = 0;
	UPROPERTY(VisibleAnywhere)
	bool IsDead = false;
	
public:
	//Setters
	UFUNCTION()
	void SetLengthScore(int NewLengthScore);
	UFUNCTION()
	void AddLengthScore(int Increment);
	UFUNCTION()
	virtual void SetDeathStatus(bool DeathStatus);

	//Getters
	UFUNCTION()
	int GetLengthScore();
	UFUNCTION()
	bool GetDeathStatus();
};
