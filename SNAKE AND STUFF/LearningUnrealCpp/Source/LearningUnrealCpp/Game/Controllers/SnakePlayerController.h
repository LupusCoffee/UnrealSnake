// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

class ARollaBallPlayer;
class UBaseMovementDataConfig;
class UInputMappingContext;

UCLASS()
class LEARNINGUNREALCPP_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()
	virtual void OnPossess(APawn* InPawn) override;

protected:
	//Player and Input Setup
	UPROPERTY()
	ARollaBallPlayer* MyPlayer;
	UFUNCTION()
	void SetupPlayer(APawn* InPawn);
	UFUNCTION()
	void SetupInput();
	
	// INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UBaseMovementDataConfig* InputActions;
};
