// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerStateBase.h"
#include "HighScorePlayerState.generated.h"

UCLASS()
class LEARNINGUNREALCPP_API AHighScorePlayerState : public APlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	AHighScoreGameState* HighScoreGameState;
	UPROPERTY(VisibleAnywhere)
	ARollaBallPlayer* PlayerPawn;
	
public:
	UFUNCTION() int GetLengthScore();
	UFUNCTION() void SetLengthScore(ARollaBallPlayer* Player, int NewLengthScore);
	virtual void SetDeathStatus(bool DeathStatus) override;
	UFUNCTION() void SetPlayerPawn(ARollaBallPlayer* Pawn);
};
