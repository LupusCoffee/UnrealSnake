// Fill out your copyright notice in the Description page of Project Settings.


#include "LocateClosestValidGate.h"

#include "CollisionDebugDrawingPublic.h"
#include "Kismet/GameplayStatics.h"
#include "LearningUnrealCpp/Game/BattleMode/BattleGameState.h"
#include "LearningUnrealCpp/Items/RollaBallItemBase.h"

void ULocateClosestValidGate::StartTask()
{
	if (AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(GetWorld()))
	{
		HighScoreGameState = Cast<AHighScoreGameState>(GameStateBase);
		BattleGameState = Cast<ABattleGameState>(GameStateBase);
	}
}

FVector ULocateClosestValidGate::RunTask(FVector StartPosition)
{
	//ugh all of this is so disgusting
	FVector ClosestLocation = FVector(0,0,1000000000);
	
	if (HighScoreGameState)
	{
		if (HighScoreGameState->GetAllGates().Num() <= 0)
		{
			FinishExecute(true);
			return FVector::ZeroVector;
		}
		
		for (auto Gate : HighScoreGameState->GetAllGates())
		{
			if (Gate->GetCurrentCooldown() > 0) continue;

			if ((StartPosition - Gate->GetActorLocation()).Length() < (StartPosition - ClosestLocation).Length())
				ClosestLocation = Gate->GetActorLocation();
		}
	}
	if (BattleGameState)
	{
		
	}
	
	FinishExecute(true);
	return ClosestLocation;
}
