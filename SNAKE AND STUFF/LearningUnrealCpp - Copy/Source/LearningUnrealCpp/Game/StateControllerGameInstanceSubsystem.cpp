// Fill out your copyright notice in the Description page of Project Settings.


#include "StateControllerGameInstanceSubsystem.h"

ESkibidiState UStateControllerGameInstanceSubsystem::GetState()
{
	return SkibidiState;
}

void UStateControllerGameInstanceSubsystem::SetState(::ESkibidiState State)
{
	SkibidiState = State;

	//Printing lol
	
	switch (SkibidiState)
	{
		case ESkibidiState::MENU:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString("Switched to menu state."));
			break;
		case ESkibidiState::HIGHSCORE:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString("Switched to highscore state."));
			break;
		case ESkibidiState::BATTLE:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString("Switched to battle state."));
			break;
		case ESkibidiState::OUTRO:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString("Switched to outro state."));
			break;
	}
}
