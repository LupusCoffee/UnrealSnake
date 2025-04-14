// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "BaseMovementDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API UBaseMovementDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveForward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveRight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Jump;
};
