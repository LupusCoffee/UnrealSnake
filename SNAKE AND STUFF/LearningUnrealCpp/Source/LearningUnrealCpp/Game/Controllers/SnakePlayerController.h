// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

class UBaseMovementDataConfig;
class UInputMappingContext;

UCLASS()
class LEARNINGUNREALCPP_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UBaseMovementDataConfig* InputActions;
};
