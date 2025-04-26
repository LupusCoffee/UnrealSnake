// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreMode/HighScoreGameState.h"
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
	virtual void SetDeathStatus(bool DeathStatus);

	//Getters
	UFUNCTION()
	bool GetDeathStatus();
};
