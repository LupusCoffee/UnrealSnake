// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StateControllerGameInstanceSubsystem.generated.h"

/**
 * A state controller subsystem, as a child of GameInstanceSubsystem
 */
UENUM(BlueprintType)
enum class ESkibidiState : uint8 {
	MENU = 0		UMETA(DisplayName = "MENU"),
	HIGHSCORE = 1	UMETA(DisplayName = "HIGHSCORE"),
	BATTLE = 2		UMETA(DisplayName = "BATTLE"),
	OUTRO = 3		UMETA(DisplayName = "OUTRO")
};

UCLASS()
class LEARNINGUNREALCPP_API UStateControllerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ESkibidiState GetState();
	UFUNCTION(BlueprintCallable)
	void SetState(ESkibidiState State);
	
protected:
	ESkibidiState SkibidiState = ESkibidiState::MENU;
};
