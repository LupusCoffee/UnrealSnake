// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningUnrealCpp/Game/PlayerStateBase.h"
#include "BattlePlayerState.generated.h"

class ABattleGameState;

UCLASS()
class LEARNINGUNREALCPP_API ABattlePlayerState : public APlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	ABattleGameState* BattleGameState;
	UPROPERTY(VisibleAnywhere)
	ARollaBallPlayer* PlayerPawn;

public:
	virtual void SetDeathStatus(bool DeathStatus) override;
	UFUNCTION() void SetPlayerPawn(ARollaBallPlayer* Pawn);
};
